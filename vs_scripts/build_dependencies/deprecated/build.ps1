param (
	[Parameter(Mandatory = $true)] [string]$solutionDirectory,
	[Parameter(Mandatory = $true)] [string]$configuration,
	[Parameter(Mandatory = $true)] [string]$platform
)

Write-Output "build_dependencies.ps1 running"
Write-Output "solution directory: $solutionDirectory"
Write-Output "configuration:      $configuration"
Write-Output "platform:           $platform"

$rootDirectory = $PSScriptRoot
$box2dBuildScript = "build_box2d_solution.ps1"
$glewBuildScript = "build_glew_solution.ps1"
$glfwBuildScript = "build_glfw_solution.ps1"

& "$rootDirectory\$box2dBuildScript" -solutionDirectory $solutionDirectory -configuration $configuration -platform $platform
& "$rootDirectory\$glfwBuildScript" -solutionDirectory $solutionDirectory -configuration $configuration -platform $platform
& "$rootDirectory\$glewBuildScript" -solutionDirectory $solutionDirectory -configuration $configuration -platform $platform
