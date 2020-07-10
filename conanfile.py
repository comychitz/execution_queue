from conans import ConanFile

# packaging as header only library
class ExecutionQueueConan(ConanFile):
    name = "ExecutionQueue"
    version = "01.00.00"
    exports_sources = "src/*"
    no_copy_source = True

    def package(self):
        self.copy("*.h", dst="include", keep_path=False)

    def package_id(self):
        self.info.header_only()
