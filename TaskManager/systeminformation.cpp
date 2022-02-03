#include "systeminformation.h"
#include <string>
#include <QString>

SystemInformation::SystemInformation()
{
}

char *concat(const char *a, const char *b){
    int lena = strlen(a);
    int lenb = strlen(b);
    char *con = (char*)malloc(lena+lenb+1);

    memcpy(con,a,lena);
    memcpy(con+lena,b,lenb+1);
    return con;
}

void add_spaces(char *dest, int num_of_spaces) {
    int len = strlen(dest);
    memset( dest+len, ' ', num_of_spaces );
    dest[len + num_of_spaces] = '\0';
}

char* SystemInformation::getRelease()
{
    struct utsname uname_pointer;
    uname(&uname_pointer);
    char * system_name = uname_pointer.sysname;
    add_spaces(system_name,1);
    char * release_name = uname_pointer.release;
    add_spaces(release_name,1);
    char *value_1 = concat(system_name, release_name);
    char *node_name = uname_pointer.nodename;
    add_spaces(node_name,1);
    char *version_name = uname_pointer.version;
    add_spaces(version_name,1);
    char *value_2 = concat(node_name, version_name);
    char *machine_name = uname_pointer.machine;
    add_spaces(machine_name,1);
    char *domain_name = uname_pointer.domainname;
    add_spaces(domain_name,1);
    char *value_3 = concat(machine_name, domain_name);

    char *final_val1 = concat(value_1, value_2);
    char *final_val2 = concat(final_val1, value_3);
	
    return final_val2;
}

char *SystemInformation::getModel()
{
    char *model_name;
    char *cpu_cores;

    FILE *fp = fopen("/proc/cpuinfo", "r");

    size_t n = 0;
    char *line = NULL;
    while (getline(&line, &n, fp) > 0) 
	{
		if (strstr(line, "model name\t:"))
		{
			model_name = line;
			break;
		}
    }

	fclose(fp);

	return model_name;
}

char *SystemInformation::getStorage()
{
    char *mem_total = NULL;
	FILE *fe = fopen("/proc/meminfo", "r");
	size_t m = 0;
	char *l = NULL;
	
	while (getline(&l, &m ,fe) > 0) 
	{
		if (strstr(l, "MemTotal"))
		{
			mem_total = l;
			break;
		}
	}

	fclose(fe);

	//HARD DISK CAPACITY
	char *capacity;
	FILE *f_3 = fopen("/sys/block/sda/size", "r");
	size_t n_3 = 0;
	char *line_3 = NULL;
	
	while (getline(&line_3, &n_3 ,f_3) > 0) {
	}
	capacity = line_3;

	fclose(f_3);

	add_spaces(mem_total, 1);
	char * final = concat(mem_total,capacity);
	
	return final;
}




