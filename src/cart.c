#include "cart.h"

static const char *ROM_TYPES[0x100] = {
    [0x00] = "ROM ONLY",
    [0x01] = "MBC1",
    [0x02] = "MBC1+RAM",
    [0x03] = "MBC1+RAM+BATTERY",
    [0x04] = "0x04 ???",
    [0x05] = "MBC2",
    [0x06] = "MBC2+BATTERY",
    [0x07] = "0x07 ???",
    [0x08] = "ROM+RAM 1",
    [0x09] = "ROM+RAM+BATTERY 1",
    [0x0A] = "0x0A ???",
    [0x0B] = "MMM01",
    [0x0C] = "MMM01+RAM",
    [0x0D] = "MMM01+RAM+BATTERY",
    [0x0E] = "0x0E ???",
    [0x0F] = "MBC3+TIMER+BATTERY",
    [0x10] = "MBC3+TIMER+RAM+BATTERY 2",
    [0x11] = "MBC3",
    [0x12] = "MBC3+RAM 2",
    [0x13] = "MBC3+RAM+BATTERY 2",
    [0x14] = "0x14 ???",
    [0x15] = "0x15 ???",
    [0x16] = "0x16 ???",
    [0x17] = "0x17 ???",
    [0x18] = "0x18 ???",
    [0x19] = "MBC5",
    [0x1A] = "MBC5+RAM",
    [0x1B] = "MBC5+RAM+BATTERY",
    [0x1C] = "MBC5+RUMBLE",
    [0x1D] = "MBC5+RUMBLE+RAM",
    [0x1E] = "MBC5+RUMBLE+RAM+BATTERY",
    [0x1F] = "0x1F ???",
    [0x20] = "MBC6",
    [0x21] = "0x21 ???",
    [0x22] = "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    [0xFC] = "POCKET CAMERA",
    [0xFD] = "BANDAI TAMA5",
    [0xFE] = "HuC3",
    [0xFF] = "HuC1+RAM+BATTERY"
};

static const char *LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

static const char *RAM_SIZE[0x6] = {
    [0x00] = "No RAM",
    [0x01] = "Unused",
    [0x02] = "8 KiB / 1 bank",
    [0x03] = "32 KiB / 4 banks of 8 KiB each",
    [0x04] = "128 KiB / 16 banks of 8 KiB each",
    [0x05] = "64 KiB / 8 banks of 8 KiB each"
};

const char *cart_type_name(cart_header_t *cart_header) {
    if (cart_header->cart_type <= 0xFF) {
        return ROM_TYPES[cart_header->cart_type];
    }
    return "UNKNOWN";
}

const char *cart_lic_name(cart_header_t *cart_header) {
    if (cart_header->new_lic_code <= 0xA4) {
        return LIC_CODE[cart_header->new_lic_code];
    }
    return "UNKNOWN";
}

const char *cart_ram_size(cart_header_t *cart_header) {
    if (cart_header->ram_size <= 0x05)
        return RAM_SIZE[cart_header->ram_size];
    return "UNKNOWN";
}
bool cart_load(char *cart_path, cart_t *cart) {
    FILE *cart_ptr;
    cart_ptr = fopen(cart_path,"r");

    // Checking if the file was opened successfully 
    if (cart_ptr == NULL) {
        printf("Failed to open: %s\n", cart_path);
        return false;
    }

    printf("Opened: %s\n", cart->filename);

    fseek(cart_ptr, 0, SEEK_END);
    cart->rom_size = ftell(cart_ptr);

    rewind(cart_ptr);

    cart->rom_data = malloc(cart->rom_size);
    fread(cart->rom_data, cart->rom_size, 1, cart_ptr);
    fclose(cart_ptr);

    // ROM HEADER entry point start at 0x100 offset from cartride ROM base-address 
    cart->header = (cart_header_t *)(cart->rom_data + 0x100);
    uint8_t lo = cart->header->new_lic_code & 0xFF;
    uint8_t hi = cart->header->new_lic_code >> 8;
    printf("First and 2nd byte of lic code %X - %X\n", lo, hi);
    printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", cart->header->title);
    printf("\t Type     : %2.2X (%s)\n", cart->header->cart_type, cart_type_name(cart->header));
    printf("\t ROM Size : %d KB\n", 32 << cart->header->rom_size);
    printf("\t RAM Size : %2.2X (%s)\n", cart->header->ram_size, cart_ram_size(cart->header));
    printf("\t LIC Code : %2.2X (%s)\n", cart->header->new_lic_code, cart_lic_name(cart->header));
    printf("\t ROM Vers : %2.2X\n", cart->header->version);
    return true;
}