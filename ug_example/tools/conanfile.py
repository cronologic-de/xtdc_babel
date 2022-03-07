#
# Conan recipe used to create the source package of the `crono_dma_driver`
# for the compliant platform.
#
# For Linux, it installs `crono_dma_driver`, for the builder to be able
# to build `xtdc4_driver.a` static libary from its source.
#
import sys
sys.path.append("conan_utils/")
from CronoConanBase import CronoConanBase

class CronoXTDC4UgExConan(CronoConanBase):
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
    url = "https://crono.jfrog.io/artifactory/dev/_/_/xtdc4_ug_example" \
        + version
    description = "TDC4 Driver User Guide Example"
    topics = ["cronologic-de", "TDC4", "PCI", "PCIe"]
    settings = ["os", "compiler", "build_type", "arch"]

    # `CronoConanBase` variables initialization and export
    supported_os = ["Windows", "Linux"]
    proj_src_indir = ".."
    exports = "conan_utils/*.py"
    export_source = True

    # ==========================================================================
    # Conan Methods
    #
    def requirements(self):
        self.requires(self.xtdc4_driver_pkg_ref)

    # __________________________________________________________________________
    #
    def package(self):
        super().package(pack_src=True, exec_name="xtdc4_ugex")

    # __________________________________________________________________________
