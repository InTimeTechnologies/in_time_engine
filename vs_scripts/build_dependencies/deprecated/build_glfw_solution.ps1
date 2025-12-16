# Script parameters
param (
	[Parameter(Mandatory = $true)] [string]$solutionDirectory,
	[Parameter(Mandatory = $true)] [string]$configuration,
	[Parameter(Mandatory = $true)] [string]$platform
)

# Constants
$glfwDependencyDirectory = Join-Path $solutionDirectory "dependencies\glfw"
$glfwBuildDirectory      = Join-Path $glfwDependencyDirectory "build\$configuration"
$glfwInstallDirectory    = Join-Path $glfwDependencyDirectory "install\$configuration"

# Value report
Write-Output "build_glfw_solution.ps1 running"
Write-Output "solutionDirectory:       $solutionDirectory"
Write-Output "configuration:           $configuration"
Write-Output "platform:                $platform"
Write-Output "glfwDependencyDirectory: $glfwDependencyDirectory"
Write-Output "glfwBuildDirectory:      $glfwBuildDirectory"
Write-Output "glfwInstallDirectory:    $glfwInstallDirectory"

# Ensure build directory exists
if (-not (Test-Path $glfwBuildDirectory)) {
    New-Item -Path $glfwBuildDirectory -ItemType Directory | Out-Null
}

# Change to build directory
Push-Location "$glfwBuildDirectory"
Write-Output "Current working directory: $(Get-Location)"

# Configure with CMake
$cmakeGenerator = 'Visual Studio 17 2022'
& cmake "$glfwDependencyDirectory" -G $cmakeGenerator -A $platform -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="$glfwInstallDirectory"

# Build and install
& cmake --build . --config $configuration --target install -- /m

# Return to original directory
Pop-Location

# Exit with the same code as last command
exit $LASTEXITCODE
