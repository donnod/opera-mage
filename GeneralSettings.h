#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <string>

using namespace std;

namespace Settings {

	static int as_port = 22222;
	static const char *as_host = "127.0.0.1";
	// static const char *as_host = "192.168.1.62";

	static int fe_port = 33333;
	static const char *fe_host = "127.0.0.1";
	// static const char *fe_host = "192.168.1.62";

	// spid, subscription_pri_key, subscription_sec_key and ias_url
	// are provided by Intel after registration for the IAS service
	static string spid = "";
	static string subscription_pri_key = "";
	static string subscription_sec_key = "";
	static string ias_url = "https://api.trustedservices.intel.com/sgx/dev";

	static uint8_t asie_target_info[] = {0};
	static uint8_t asae_target_info[] = {0};
	static uint8_t isve_target_info[] = {0};
}

#endif
