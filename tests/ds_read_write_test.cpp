#include <cassert>
#include <cstdint>

static void ds_write_b16(uint32_t* mem, uint32_t base, uint32_t offset, uint32_t data)
{
    uint32_t addr = base + offset;
    uint32_t aligned = addr & ~3u;
    uint32_t shift = (addr & 3u) * 8u;
    uint32_t word = mem[aligned / 4];
    uint32_t mask = 0xFFFFu << shift;
    word = (word & ~mask) | ((data & 0xFFFFu) << shift);
    mem[aligned / 4] = word;
}

static uint32_t ds_read_u16(uint32_t* mem, uint32_t base, uint32_t offset)
{
    uint32_t addr = base + offset;
    uint32_t aligned = addr & ~3u;
    uint32_t shift = (addr & 3u) * 8u;
    uint32_t word = mem[aligned / 4];
    return (word >> shift) & 0xFFFFu;
}

int main()
{
    uint32_t mem[4] = {0xAABBCCDD, 0, 0, 0};
    ds_write_b16(mem, 0, 2, 0x1122);
    assert(mem[0] == 0x1122CCDD);
    uint32_t val = ds_read_u16(mem, 0, 2);
    assert(val == 0x1122);

    ds_write_b16(mem, 0, 0, 0x3344);
    assert(mem[0] == 0x11223344);
    val = ds_read_u16(mem, 0, 0);
    assert(val == 0x3344);
    return 0;
}
