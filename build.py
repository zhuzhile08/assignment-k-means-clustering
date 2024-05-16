import os
import sys
import subprocess as subp

def main(*args):
    # make build directory
    currentDir = os.getcwd()
    buildDir = os.path.join(currentDir, "build")

    if not os.path.exists(buildDir):
        os.makedirs(buildDir)

    # update or clone submodules
    print("Update dependencies:")
    subp.run(["git", "pull"])
    subp.run(["git", "submodule", "update", "--init", "--recursive"])

    cmakeArgs = [*args]

    print("Generate CMake files:")
    subp.run(["cmake", ".."] + cmakeArgs, cwd=buildDir)
    
    print("Build dependencies and executable:")
    subp.run(["cmake", "--build", "."], cwd=buildDir)

if __name__ == "__main__":
    args = []

    if len(sys.argv) > 0:
        args += sys.argv[1:]

    main(*args)