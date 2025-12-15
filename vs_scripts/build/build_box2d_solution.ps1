# Script parameters
param (
	[Parameter(Mandatory = $true)] [string]$solutionDirectory,
	[Parameter(Mandatory = $true)] [string]$configuration,
	[Parameter(Mandatory = $true)] [string]$platform
)

# Constants
$box2dDependencyDirectory = Join-Path $solutionDirectory "dependencies\box2d"
$box2dBuildDirectory      = Join-Path $box2dDependencyDirectory "build\$configuration"
$box2dInstallDirectory    = Join-Path $box2dDependencyDirectory "install\$configuration"

# Value report
Write-Output "build_box2d_solution.ps1 running"
Write-Output "solutionDirectory:        $solutionDirectory"
Write-Output "configuration:            $configuration"
Write-Output "platform:                 $platform"
Write-Output "box2dDependencyDirectory: $box2dDependencyDirectory"
Write-Output "box2dBuildDirectory:      $box2dBuildDirectory"
Write-Output "box2dInstallDirectory:    $box2dInstallDirectory"

# Ensure build directory exists
if (-not (Test-Path $box2dBuildDirectory)) {
    New-Item -Path $box2dBuildDirectory -ItemType Directory | Out-Null
}

# Change to build directory
Push-Location "$box2dBuildDirectory"
Write-Output "Current working directory: $(Get-Location)"

# Configure with CMake
$cmakeGenerator = 'Visual Studio 17 2022'
& cmake "$box2dDependencyDirectory" -G $cmakeGenerator -A $platform -DCMAKE_INSTALL_PREFIX="$box2dInstallDirectory"

# Build and install
& cmake --build . --config $configuration --target install -- /m

# Return to original directory
Pop-Location

# Exit with the same code as last command
exit $LASTEXITCODE
