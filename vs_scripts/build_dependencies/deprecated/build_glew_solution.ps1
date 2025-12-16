# Script parameters
param (
    [Parameter(Mandatory = $true)] [string]$solutionDirectory,
    [Parameter(Mandatory = $true)] [string]$configuration,
    [Parameter(Mandatory = $true)] [string]$platform
)

# Constants
$dependencyDirectory       = Join-Path $solutionDirectory "dependencies"
$glewDependencyDirectory   = Join-Path $dependencyDirectory "glew"
$glewBuildDirectory        = Join-Path $glewDependencyDirectory "build\vc15"
$glewUrl                   = "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
$zipFilePath               = Join-Path $dependencyDirectory "glew.zip"
$extractedFileName         = "glew-2.2.0"
$extractedFileNewName      = "glew"

# Report
Write-Output "build_glew_solution.ps1 running"
Write-Output "solutionDirectory:       $solutionDirectory"
Write-Output "configuration:           $configuration"
Write-Output "platform:                $platform"
Write-Output "dependencyDirectory:     $dependencyDirectory"
Write-Output "glewDependencyDirectory: $glewDependencyDirectory"
Write-Output "glewBuildDirectory:      $glewBuildDirectory"
Write-Output "glewUrl:                 $glewUrl"
Write-Output "zipFilePath:             $zipFilePath"
Write-Output "extractedFileName:       $extractedFileName"
Write-Output "extractedFileNewName:    $extractedFileNewName"

# Ensure dependencies folder exists
if (-not (Test-Path $dependencyDirectory)) {
    New-Item -Path $dependencyDirectory -ItemType Directory | Out-Null
}

# Only download and extract GLEW if it does not exist
if (Test-Path $glewDependencyDirectory) {
    Write-Output "Found GLEW dependency directory. Skipping download."
} else {
    Write-Output "Downloading GLEW to $zipFilePath..."
    Invoke-WebRequest -Uri $glewUrl -OutFile $zipFilePath

    Write-Output "Extracting GLEW..."
    Expand-Archive -Path $zipFilePath -DestinationPath $dependencyDirectory -Force

    # Rename extracted folder to standard name
    $originalPath = Join-Path $dependencyDirectory $extractedFileName
    $newPath      = Join-Path $dependencyDirectory $extractedFileNewName
    if (Test-Path $originalPath) {
        Rename-Item -Path $originalPath -NewName $extractedFileNewName
    }

    # Remove zip file
    Remove-Item $zipFilePath -Force
}

# Ensure build directory exists
if (-not (Test-Path $glewBuildDirectory)) {
    New-Item -Path $glewBuildDirectory -ItemType Directory | Out-Null
}

# Build GLEW
Write-Output "Building GLEW in $glewBuildDirectory..."
Push-Location $glewBuildDirectory
try {
    $msbuildArgs = @(
        "glew.sln"
        "/p:Configuration=$configuration"
        "/p:Platform=$platform"
        "/p:PlatformToolset=v143"
        "/p:WindowsTargetPlatformVersion=10.0.22621.0"
    )

    & msbuild.exe @msbuildArgs

    if ($LASTEXITCODE -ne 0) {
        Write-Error "MSBuild failed with exit code $LASTEXITCODE"
        exit $LASTEXITCODE
    }
} finally {
    Pop-Location
}

Write-Output "GLEW build completed successfully."
