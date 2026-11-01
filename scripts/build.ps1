param(
    [string]$Compiler = "",
    [string]$Test = "tests/test_tensor.cpp"
)

# Compile all src/*.cpp plus one test file, then run the test.
# Usage: powershell -ExecutionPolicy Bypass -File scripts/build.ps1
# g++ is taken from PATH; if it is not there, pass -Compiler "<path to g++.exe>".

$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot

Push-Location $root
try {
    if ([string]::IsNullOrWhiteSpace($Compiler)) {
        $found = Get-Command g++ -CommandType Application -ErrorAction SilentlyContinue | Select-Object -First 1
        if (-not $found) {
            throw "g++ not found on PATH. Add the MinGW bin folder to PATH, or pass -Compiler '<path to g++.exe>'."
        }
        $Compiler = $found.Source
    }

    if (-not (Test-Path $Compiler)) {
        throw "Compiler not found: $Compiler. Pass -Compiler with the full path to g++.exe."
    }

    # MinGW needs its own bin/ on PATH so cc1plus and runtime DLLs are found.
    $compilerDir = Split-Path -Parent $Compiler
    $env:PATH = $compilerDir + ";" + $env:PATH

    New-Item -ItemType Directory -Force -Path build | Out-Null

    $sources = @(Get-ChildItem -Path src -Filter *.cpp -Recurse | ForEach-Object { $_.FullName })
    if ($sources.Count -eq 0) {
        throw "No .cpp files found under src/."
    }

    $testName = [System.IO.Path]::GetFileNameWithoutExtension($Test)
    $out = Join-Path (Join-Path $root "build") ($testName + ".exe")
    $compileArgs = @("-std=c++17", "-O2", "-Wall", "-Wextra", "-Iinclude", $Test) + $sources + @("-o", $out)

    Write-Host "g++ $($compileArgs -join ' ')" -ForegroundColor DarkGray
    & $Compiler @compileArgs
    if ($LASTEXITCODE -ne 0) {
        throw "Compile failed with exit code $LASTEXITCODE."
    }

    & $out
    exit $LASTEXITCODE
}
finally {
    Pop-Location
}
