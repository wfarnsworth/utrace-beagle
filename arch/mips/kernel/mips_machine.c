/*
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 *
 */
#include <linux/mm.h>
#include <linux/string.h>

#include <asm/mips_machine.h>

static struct list_head mips_machines __initdata =
		LIST_HEAD_INIT(mips_machines);
static char *mips_machid __initdata;

char *mips_machine_name = "Unknown";

static struct mips_machine * __init mips_machine_find(unsigned long machtype)
{
	struct list_head *this;

	list_for_each(this, &mips_machines) {
		struct mips_machine *mach;

		mach = list_entry(this, struct mips_machine, list);
		if (mach->mach_type == machtype)
			return mach;
	}

	return NULL;
}

void __init mips_machine_register(struct mips_machine *mach)
{
	list_add_tail(&mach->list, &mips_machines);
}

void __init mips_machine_set_name(char *name)
{
	unsigned int len;
	char *p;

	if (name == NULL)
		return;

	len = strlen(name);
	p = kmalloc(len + 1, GFP_KERNEL);
	if (p) {
		strncpy(p, name, len);
		p[len] = '\0';
		mips_machine_name = p;
	} else {
		printk(KERN_WARNING "MIPS: no memory for machine_name\n");
	}
}

void __init mips_machine_setup(void)
{
	struct mips_machine *mach;

	mach = mips_machine_find(mips_machtype);
	if (!mach) {
		printk(KERN_WARNING "MIPS: no machine registered for "
			"machtype %lu\n", mips_machtype);
		return;
	}

	mips_machine_set_name(mach->mach_name);
	printk(KERN_NOTICE "MIPS: machine is %s\n", mips_machine_name);

	if (mach->mach_setup)
		mach->mach_setup();
}

int __init mips_machtype_setup(char *id)
{
	if (mips_machid == NULL)
		mips_machid = id;

	return 1;
}

__setup("machtype=", mips_machtype_setup);

static int __init mips_machtype_init(void)
{
	struct list_head *this;
	struct mips_machine *mach;

	if (mips_machid == NULL)
		return 0;

	list_for_each(this, &mips_machines) {
		mach = list_entry(this, struct mips_machine, list);
		if (mach->mach_id == NULL)
			continue;

		if (strcmp(mach->mach_id, mips_machid) == 0) {
			mips_machtype = mach->mach_type;
			return 0;
		}
	}

	printk(KERN_WARNING
	       "MIPS: no machine found for id: '%s', registered machines:\n",
	       mips_machid);
	printk(KERN_WARNING "%32s %s\n", "id", "name");

	list_for_each(this, &mips_machines) {
		mach = list_entry(this, struct mips_machine, list);
		printk(KERN_WARNING "%32s %s\n",
		       mach->mach_id ? mach->mach_id : "", mach->mach_name);
	}

	return 0;
}

core_initcall(mips_machtype_init);
