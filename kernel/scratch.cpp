0       | uint32_t flags             |    (required)
4       | uint32_t mem_lower         |    (present if flags[0] is set)
8       | uint32_t mem_upper         |    (present if flags[0] is set)
12      | uint32_t boot_device       |    (present if flags[1] is set)
16      | uint32_t cmdline           |    (present if flags[2] is set)
20      | uint32_t mods_count        |    (present if flags[3] is set)
24      | uint32_t mods_addr         |    (present if flags[3] is set)
28 - 40 | uint32_t syms              |    (present if flags[4] or
44      | uint32_t mmap_length       |    (present if flags[6] is set)
48      | uint32_t mmap_addr         |    (present if flags[6] is set)
52      | uint32_t drives_length     |    (present if flags[7] is set)
56      | uint32_t drives_addr       |    (present if flags[7] is set)
60      | uint32_t config_table      |    (present if flags[8] is set)
64      | uint32_t boot_loader_name  |    (present if flags[9] is set)
68      | uint32_t apm_table         |    (present if flags[10] is set)
72      | uint32_t vbe_control_info  |    (present if flags[11] is set)
76      | uint32_t vbe_mode_info     |
80      | uint32_t vbe_mode          |
82      | uint32_t vbe_interface_seg |
84      | uint32_t vbe_interface_off |
86      | uint32_t vbe_interface_len |
88      | uint32_t framebuffer_addr  |    (present if flags[12] is set)
96      | uint32_t framebuffer_pitch |
100     | uint32_t framebuffer_width |
104     | uint32_t framebuffer_height|
108     | uint32_t framebuffer_bpp   |
109     | uint32_t framebuffer_type  |
110-115 | uint32_t color_info        |