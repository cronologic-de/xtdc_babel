#
# Conan recipe used to create the source package of the `crono_dma_driver`
# for the compliant platform.
#
# For Linux, it installs `crono_dma_driver`, for the builder to be able
# to build `xtdc4_driver.a` static libary from its source.
#
from conans import ConanFile

class CronoXTDC4UgExConan(ConanFile):
    python_requires = "crono_utils/0.0.1"
    python_requires_extend = "crono_utils.CronoConanBase"

    # __________________________________________________________________________
    # Values to be reviewed with every new version
    #
    version = "0.0.1"
    xtdc4_driver_pkg_name = "xtdc4_driver-bin"
    xtdc4_driver_pkg_ref = xtdc4_driver_pkg_name + "/[~0.0.1]"

    # __________________________________________________________________________
    # Member variables
    #
    name = "xtdc4_ug_example"
    license = "GPL-3.0 License"
    author = "Bassem Ramzy <SanPatBRS@gmail.com>"
    url = "https://conan.cronologic.de/artifactory/pub/_/_/xtdc4_ug_example" \
        + version
    description = "TDC4 Driver User Guide Example"
    topics = ["cronologic-de", "TDC4", "PCI", "PCIe"]
    settings = ["os", "compiler", "build_type", "arch", "distro"]

    # `CronoConanBase` variables initialization and export
    supported_os = ["Windows", "Linux"]
    proj_src_indir = ".."
    export_source = True

    # ==========================================================================
    # Conan Methods
    #
    def requirements(self):
        self.requires(self.xtdc4_driver_pkg_ref)

    # __________________________________________________________________________
    #
    def package(self):
        super().package(exec_name="xtdc4_ugex")

    # __________________________________________________________________________
