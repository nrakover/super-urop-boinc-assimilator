/*
 * assimilate_handler.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: nrakover
 */

#include <vector>
#include <string>
#include <cstdlib>

#include "boinc_db.h"
#include "error_numbers.h"
#include "filesys.h"
#include "sched_msgs.h"
#include "validate_util.h"
#include "sched_config.h"

using std::vector;
using std::string;

const char* RESULTS_DIR = "results";  //TODO: need to specify

int write_error(char* p) {
	static FILE* f = 0;
	if (!f) {
		f = fopen(config.project_path("%s/errors", RESULTS_DIR), "a");
		if (!f)
			return ERR_FOPEN;
	}
	fprintf(f, "%s", p);
	fflush(f);
	return 0;
}

int assimilate_handler(WORKUNIT& wu, vector<RESULT>& /*results*/,
		RESULT& canonical_result) {
	int retval;
	char buf[1024];
	unsigned int i;

//    retval = boinc_mkdir(config.project_path(RESULTS_DIR));
//    if (retval) return retval;

	if (wu.canonical_resultid) {
		vector<OUTPUT_FILE_INFO> output_files;
		const char *copy_path;
		get_output_file_infos(canonical_result, output_files);
		unsigned int n = output_files.size();
		bool file_copied = false;
		if (n == 2) {
			for (i = 0; i < n; i++) {
				OUTPUT_FILE_INFO& fi = output_files[i];
				if (i == 0) {
					copy_path = config.project_path("%s/trans_%s", RESULTS_DIR,
							wu.name);
				} else if (i == 1) {
					copy_path = config.project_path("%s/emi_%s", RESULTS_DIR,
							wu.name);
				}
				retval = boinc_copy(fi.path.c_str(), copy_path);
				if (!retval) {
					file_copied = true;
				}
			}
		} else if (n == 1) {
			OUTPUT_FILE_INFO& f = output_files[0];
			copy_path = config.project_path("%s/loglike_%s", RESULTS_DIR,
					wu.name);
			retval = boinc_copy(f.path.c_str(), copy_path);
			if (!retval) {
				file_copied = true;
			}
		}
		if (!file_copied) {
			copy_path = config.project_path("%s/%s_%s", RESULTS_DIR, wu.name,
					"no_output_files");
			FILE* f = fopen(copy_path, "w");
			fclose(f);
		}
	} else {
		sprintf(buf, "%s: 0x%x\n", wu.name, wu.error_mask);
		return write_error(buf);
	}
	return 0;
}
