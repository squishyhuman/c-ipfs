CC = gcc
CFLAGS = -O0 -I../include -I../../c-libp2p/include -I../../c-multihash/include -I../../c-multiaddr/ -I../../c-protobuf -g3 -Wall
LFLAGS = -L../../c-libp2p -L../../c-multihash -L../../c-multiaddr -lp2p -lm -lmultihash -lmultiaddr -lpthread -lresolv
DEPS = cmd/ipfs/test_init.h repo/test_repo_bootstrap_peers.h repo/test_repo_config.h repo/test_repo_identity.h cid/test_cid.h
OBJS = main.o \
	../blocks/block.o ../blocks/blockstore.o \
	../cid/cid.o \
	../cmd/ipfs/init.o \
	../commands/argument.o ../commands/command_option.o ../commands/command.o ../commands/cli/parse.o \
	../core/builder.o \
	../datastore/ds_helper.o \
	../datastore/key.o \
	../dnslink/dnslink.o \
	../flatfs/flatfs.o \
	../importer/importer.o ../importer/exporter.o ../importer/resolver.o \
	../path/path.o \
	../merkledag/merkledag.o ../merkledag/node.o \
	../multibase/multibase.o \
	../namesys/isdomain.o \
	../os/utils.o \
	../pin/pin.o \
	../repo/init.o \
	../repo/fsrepo/fs_repo.o ../repo/fsrepo/jsmn.o ../repo/fsrepo/lmdb_datastore.o \
	../repo/config/config.o ../repo/config/identity.o \
	../repo/config/bootstrap_peers.o ../repo/config/datastore.o ../repo/config/gateway.o \
	../repo/config/addresses.o ../repo/config/swarm.o ../repo/config/peer.o \
	../thirdparty/ipfsaddr/ipfs_addr.o \
	../unixfs/unixfs.o \
	../../c-protobuf/protobuf.o ../../c-protobuf/varint.o \
	../util/errs.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ipfs: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) ../../lmdb/libraries/liblmdb/liblmdb.a

all: ipfs

clean:
	rm -f *.o
	rm -f ipfs
