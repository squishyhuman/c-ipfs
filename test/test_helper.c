#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#include "ipfs/repo/init.h"
#include "ipfs/repo/fsrepo/fs_repo.h"
#include "ipfs/os/utils.h"

int remove_directory(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2;
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r)
   {
      r = rmdir(path);
   }

   return r;
}

int drop_and_build_repository(const char* path) {
	int retVal = 0;
	char currDirectory[strlen(path) + 20];

	if (os_utils_file_exists(path)) {
		retVal = os_utils_filepath_join(path, "config", currDirectory, 1024);
		if (retVal == 0)
			return 0;
		unlink(currDirectory);
		retVal = os_utils_filepath_join(path, "datastore", currDirectory, 1024);
		if (retVal == 0)
			return 0;
		remove_directory(currDirectory);
		retVal = os_utils_filepath_join(path, "blockstore", currDirectory, 1024);
		if (retVal == 0)
			return 0;
		remove_directory(currDirectory);
	} else {
		mkdir(path, S_IRWXU);
	}


	return make_ipfs_repository(path);
}


int drop_build_and_open_repo(const char* path, struct FSRepo** fs_repo) {
	int retVal = 0;

	retVal = drop_and_build_repository("/tmp/.ipfs");
	if (retVal == 0)
		return 0;
	retVal = ipfs_repo_fsrepo_new("/tmp/.ipfs", NULL, fs_repo);
	if (retVal == 0)
		return 0;
	retVal = ipfs_repo_fsrepo_open(*fs_repo);
	if (retVal == 0) {
		free(*fs_repo);
		return 0;
	}
	return 1;
}

