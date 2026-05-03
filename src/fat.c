#include "fstools.h"
#include "pp.h"

FST_PACK(struct fat_ebpb16_t {
	uint8_t drive_number;
	uint8_t reserved;
	uint8_t boot_signature;
	uint32_t volume_id;
	char volume_label[11];
	char system_type[8];
});

FST_PACK(struct fat_ebpb32_t {
	uint32_t fat_sectors_32;
	uint16_t flags;
	uint16_t fs_version;
	uint32_t root_cluster;
	uint16_t fs_info;
	uint16_t backup_boot_sector;
	char reserved1[12];
	uint8_t drive_number;
	uint8_t reserved2;
	uint8_t boot_signature;
	uint32_t volume_id;
	char volume_label[11];
	char system_type[8];
});

FST_PACK(struct fat_bpb_t {
	char jmp[3];
	char oem_name[8];
	uint16_t bytes_per_sector;
	uint8_t sectors_per_cluster;
	uint16_t reserved_sectors;
	uint8_t fats;
	uint16_t root_entries;
	uint16_t total_sectors_16;
	uint8_t media;
	uint16_t fat_sectors_16;
	uint16_t sectors_per_track;
	uint16_t heads;
	uint32_t hidden_sectors;
	uint32_t total_sectors_32;
	union {
		struct fat_ebpb16_t ebpb16;
		struct fat_ebpb32_t ebpb32;
	};
	char pad[420];
	uint16_t boot_signature;
});

typedef struct fat_bpb_t fat_bpb;