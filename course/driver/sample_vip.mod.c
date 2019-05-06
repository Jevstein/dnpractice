#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x31b28442, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x35413f6b, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x14563675, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x183ed329, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x88f494d4, __VMLINUX_SYMBOL_STR(alloc_etherdev_mqs) },
	{ 0x64473d80, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xfb94e1b1, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd024527a, __VMLINUX_SYMBOL_STR(eth_change_mtu) },
	{ 0xd327c887, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x43b6bdb, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F766748F217AD572317F7A7");
