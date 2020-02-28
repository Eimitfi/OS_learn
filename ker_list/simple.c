#include <linux/module.h>       /* Needed by all modules */
#include <linux/slab.h>
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */

static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static struct birthday* init_str(int day,int month,int year){
	struct birthday *person;
	person= kmalloc(sizeof(*person),GFP_KERNEL);
	person->day=day;
	person->month=month;
	person->year=year;
	INIT_LIST_HEAD(&(person->list));
	return person;
}
static int init_mod(void)
{
	struct birthday *person;
	int i=0;
	for(;i<5;i++){
		person=init_str(i,i,1990+i);
		list_add_tail(&(person->list),&birthday_list);
	}
	person=NULL;
	list_for_each_entry(person,&birthday_list,list){
		printk(KERN_INFO "year:%d month:%d day:%d",person->year,person->month,person->day);
	}
	return 0;
}

static void exit_mod(void){
	struct birthday *person,*next;
	int i=1;
	list_for_each_entry_safe(person,next,&birthday_list,list){
		list_del(&person->list);
		kfree(person);
		printk(KERN_INFO "birthday %d removed!",i);
		i++;
	}

}

module_init(init_mod);
module_exit(exit_mod);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("list data structure");
MODULE_AUTHOR("licantropo");
