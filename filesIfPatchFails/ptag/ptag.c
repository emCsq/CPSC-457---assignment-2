#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/module.h>


asmlinkage long sys_ptag(pid_t pid, char * inTag, int method){

	int newMethod = method;	
	struct task_struct *ts, *next;
	struct ptag *ttag;
	
	ts = pid_task(find_vpid((pid_t) pid), PIDTYPE_PID);	//initializes the task struct
	
	/*if(&ts->tagList.next == NULL){
		ts->tagList = kmalloc(sizeof(ts->tagList), GFP_KERNEL);
	}*/
	
	task_lock(ts);						//locks the task struct (I think)
	if (newMethod == 0) {
		ttag = kmalloc(sizeof(ttag), GFP_KERNEL);	//allocate memory for a tag node
		ttag->tag = kmalloc(sizeof(inTag), GFP_KERNEL);	//allocate memory for the tag itself
		strcpy(ttag->tag, inTag);			//set ttag->tag value to the input tag
		list_add(&ttag->tagList, &ts->tagList);		//added new tag to task_struct head

	} else if (newMethod == 1) {
		printk("Remove tag.\n");
		/*list_for_each_entry_safe(ttag, next, ts->tagList, tagList) {
			if(strcmp(ttag->tag, inTag) == 0){	//searches for the node to be deleted
				list_del(&ttag->tagList);	//deletes the tag node
				kfree(&ttag->tagList);		//frees the memory formally taken up by that note
				printk("A tag was deleted.\n");
			}
		}*/
	}

	list_for_each_entry(ttag, &ts->tagList, tagList) {	//for each entry it prints out the tags associated with that pid
		printk("For pid %d it has a tag of %s\n", pid, ttag->tag);
	}
	
	task_unlock(ts);					//unlocks the task struct (I think)


	return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emily Chow");
MODULE_DESCRIPTION("Problem 3 part a-c ~ attaches a tag to a user-specified PID and (ideally) removes a tag if requested");
