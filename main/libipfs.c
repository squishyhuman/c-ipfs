#include "ipfs/importer/exporter.h"
#include "ipfs/importer/importer.h"
#include "ipfs/libipfs.h"
#include "ipfs/namesys/namesys.h"
#include "ipfs/repo/init.h"

int ipfs_init_repository(const char* path)
{
    return make_ipfs_repository(path);
}

int ipfs_add(const char* root_dir, const char* fileName, struct Node** parent_node, struct FSRepo* fs_repo, size_t* bytes_written, int recursive)
{
    return ipfs_import_file(root_dir, fileName, parent_node, fs_repo, bytes_written, recursive);
}

int ipfs_object_get(const unsigned char* hash, const struct FSRepo* fs_repo)
{
    return ipfs_exporter_to_console(hash, fs_repo);
}

int ipfs_cat(struct Node* node, const struct FSRepo* fs_repo)
{
    return ipfs_exporter_cat_node(node, fs_repo);
}

int ipfs_dns_resolve(char **output_path, char *domain, int recursive)
{
    return ipfs_dns_lookup(output_path, domain, recursive);
}
