#include "fstools.h"
#include "pp.h"
#include "types.h"

_packed(struct fat_ebpb16_t {
	u8 drive_number;
	u8 reserved;
	u8 boot_signature;
	u32 volume_id;
	char volume_label[11];
	char system_type[8];
});

_packed(struct fat_ebpb32_t {
	u32 fat_sectors_32;
	u16 flags;
	u16 fs_version;
	u32 root_cluster;
	u16 fs_info;
	u16 backup_boot_sector;
	char reserved1[12];
	u8 drive_number;
	u8 reserved2;
	u8 boot_signature;
	u32 volume_id;
	char volume_label[11];
	char system_type[8];
});

_packed(struct fat_bpb_t {
	char jmp[3];
	char oem_name[8];
	u16 bytes_per_sector;
	u8 sectors_per_cluster;
	u16 reserved_sectors;
	u8 fats;
	u16 root_entries;
	u16 total_sectors_16;
	u8 media;
	u16 fat_sectors_16;
	u16 sectors_per_track;
	u16 heads;
	u32 hidden_sectors;
	u32 total_sectors_32;
	union {
		struct fat_ebpb16_t ebpb16;
		struct fat_ebpb32_t ebpb32;
	};
	char pad[420];
	u16 boot_signature;
});

typedef struct fat_bpb_t fat_bpb;