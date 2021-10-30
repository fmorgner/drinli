from conans import ConanFile, CMake
from conans.tools import collect_libs, ConanInvalidConfiguration


class DrinliConan(ConanFile):
    name = "drinli"
    description = "An experiment in building a bare-metal firmware for ARM systems"
    license = "3-Clause-BSD"
    version = "1.0.0"
    topics = "bare-metal", "arm", "embedded", "toolkit"
    url = "https://github.com/fmorgner/drinli"
    homepage = url

    generators = "cmake"

    options = {
        "perform_ipo": [False, True],
        "stack_size": range(128, 32768, 64),
    }
    default_options = {
        "perform_ipo": True,
        "stack_size": 256,
    }
    settings = "arch", "build_type", "compiler"

    build_requires = [
        "cmake/[~=3.21]",
    ]

    scm = {
        "type": "git",
        "url": "https://github.com/fmorgner/drinli.git",
        "revision": "auto",
    }

    _cmake: CMake = None

    @property
    def cmake(self) -> CMake:
        if not self._cmake:
            self._cmake = CMake(self)
            if self.settings.compiler == "gcc":
                self._cmake.definitions[
                    "CMAKE_TOOLCHAIN_FILE"
                ] = "cmake/Toolchains/arm-none-eabi-gcc.cmake"
            else:
                raise ConanInvalidConfiguration(
                    f"Unsupported compiler: ${self.settings.compiler}"
                )
            self._cmake.definitions["DRINLI_PERFORM_IPO"] = self.options.perform_ipo
            self._cmake.definitions["DRINLI_STACK_SIZE"] = self.options.stack_size
            self._cmake.configure()
        return self._cmake

    def build(self) -> None:
        self.cmake.build()

    def package(self) -> None:
        self.cmake.install()
        self.copy("LICENSE", dst="licenses", keep_path=False)

    def package_info(self) -> None:
        self.cpp_info.includedirs = ["include/drinli"]
        self.cpp_info.builddirs = ["lib/cmake"]
        self.cpp_info.libdirs = ["lib/drinli"]
        self.cpp_info.libs = collect_libs(self)
