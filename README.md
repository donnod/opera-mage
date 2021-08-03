# OPERA-MAGE: Open Remote Attestation for Intel's Secure Enclaves (MAGE version)

OPERA-MAGE is a MAGE version of OPERA, which is an Open Platform for Enclave Remote Attestation. [MAGE](https://github.com/donnod/linux-sgx-mage) is a framework that supports mutual attestation for a group of enclaves without trusted third parties.

OPERA-MAGE is extended from an prototype implementation of the following paper:

**`[CCS'19]`OPERA: Open Remote Attestation for Intel’s Secure Enclaves**  
Guoxing Chen, Yinqian Zhang, Ten-Hwang Lai  
_ACM Conference on Computer and Communications Security_, London, UK, Nov. 2019.

For more details about this project, please go to [OPERA Knowledge Base](https://sites.google.com/site/operasgxkb/home)


Build Instructions
------------
- Follow the build instructions of [linux-sgx-mage](https://github.com/donnod/linux-sgx-mage) and update `ROOT_DIR` in `libsgx_as/buildenv.mk` with the path to the built linux-sgx-mage SDK.
- Register with Intel Attestation Service [EPID](https://api.portal.trustedservices.intel.com/EPID-attestation) and update `spid, subscrption keys and ias_url` in `GeneralSettings.h`.
- Compile and run `FrontEnd`, `AServiceProvider`, `AService` and `ISV` (for MAGE to be effective in the current implementation, please recompile  `AServiceProvider` and `AService`once again).
