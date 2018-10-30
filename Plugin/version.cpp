#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {
	void getOptionsByINI(RunOptions *options) {

		// exeのパスを見つける
		wchar_t exe_path[1024];
		wchar_t drive[8];
		wchar_t dir[1024];
		wchar_t fname[128];
		wchar_t ext[128];

		GetModuleFileName(NULL, exe_path, 1024);

		_wsplitpath_s(exe_path, drive, dir, fname, ext);

		std::wstring newDir = std::wstring();
		newDir.append(dir);
		newDir.append(L"plugins");

		wchar_t ini_path[1024];
		_wmakepath_s(ini_path, drive, newDir.c_str(),L"plugin",L"ini");

		wchar_t *buf = new wchar_t[64];
		DWORD  ret;

		ret = GetPrivateProfileString(
			L"options",
			L"MenuDateFormat",
			L"no",
			buf,
			64,
			ini_path
		);

		options->MENU_DATE_FORAMT = lstrcmpW(buf, L"yes") == 0 ? true : false;
	}

	CK2Version getVersion() {

		CK2Version version = UNKNOWN;

		// _ _ 2.7.
		byte_pattern::temp_instance().find_pattern("00 00 32 2E 37 2E");
		if (byte_pattern::temp_instance().has_size(1,"v2.7.X pattern Check")) {
			version = v2_7_X;
			goto A;
		}

		// _ _ 2.8.
		byte_pattern::temp_instance().find_pattern("00 00 32 2E 38 2E");
		if (byte_pattern::temp_instance().has_size(1,"v2.8.X pattern Check")) {
			version = v2_8_X;
			goto A;
		}

		// _ _ 2.9.
		byte_pattern::temp_instance().find_pattern("00 00 32 2E 39 2E");
		if (byte_pattern::temp_instance().has_size(1,"v2.9.X pattern Check")) {
			version = v2_9_X;
			goto A;
		}

	A:
		byte_pattern::debug_output2(Misc::versionString(version));
		return version;
	}

	std::string versionString(CK2Version version) {
		switch (version) {
		case v2_7_X:
			return "v2_7_X";
		case v2_8_X:
			return "v2_8_X";
		case v2_9_X:
			return "v2_9_X";
		default:
			return "UNKNOWN";
		}
	}
}