// /* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2001-2015
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 * Joe Hershberger, National Instruments
 */

#ifndef __ETH_INTERNAL_H
#define __ETH_INTERNAL_H

/* Do init that is common to driver model and legacy networking */
void eth_common_init(void);

/**
 * eth_env_set_enetaddr_by_index() - set the MAC address environment variable
 *
 * This sets up an environment variable with the given MAC address (@enetaddr).
 * The environment variable to be set is defined by <@base_name><@index>addr.
 * If @index is 0 it is omitted. For common Ethernet this means ethaddr,
 * eth1addr, etc.
 *
 * @base_name:	Base name for variable, typically "eth"
 * @index:	Index of interface being updated (>=0)
 * @enetaddr:	Pointer to MAC address to put into the variable
 * @return 0 if OK, other value on error
 */
int eth_env_set_enetaddr_by_index(const char *base_name, int index,
				 uchar *enetaddr);

int eth_mac_skip(int index);
void eth_current_changed(void);
#ifdef CONFIG_DM_ETH
void eth_set_dev(struct udevice *dev);
#else
void eth_set_dev(struct eth_device *dev);
#endif
void eth_set_current_to_next(void);

#endif
-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>

#ifdef CONFIG_CMD_GO

/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec(ulong (*entry)(int, char * const []), int argc,
				 char * const argv[])
{
	return entry (argc, argv);
}

static int do_go(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

	addr = simple_strtoul(argv[1], NULL, 16);

	printf ("## Starting application at 0x%08lX ...\n", addr);

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1, argv + 1);
	if (rc != 0) rcode = 1;

	printf ("## Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr'",
	"addr [arg ...]\n    - start application at address 'addr'\n"
	"      passing 'arg' as arguments"
);

#endif

U_BOOT_CMD(
	reset, 1, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);

#ifdef CONFIG_CMD_POWEROFF
U_BOOT_CMD(
	poweroff, 1, 0,	do_poweroff,
	"Perform POWEROFF of the device",
	""
);
#endif
