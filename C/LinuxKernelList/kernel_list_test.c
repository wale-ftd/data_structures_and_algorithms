#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>

struct score
{
	int num;
	int english;
	int math;
	struct list_head list;
};

struct list_head score_head;
struct score stu1, stu2, stu3;
/* 定义一个遍历链表的循环游标 */
struct list_head *pos;
/* 遍历链表时，暂存链表节点 */
struct score *tmp;


static int __init chrdev_init(void)
{	
	printk(KERN_DEBUG "chrdev_init\n");

	INIT_LIST_HEAD(&score_head);

	stu1.num = 1;
	stu1.english = 90;
	stu1.math = 95;
	list_add_tail(&(stu1.list), &score_head);
	
	stu2.num = 2;
	stu2.english = 91;
	stu2.math = 96;
	list_add_tail(&(stu2.list), &score_head);
	
	stu3.num = 3;
	stu3.english = 92;
	stu3.math = 97;
	list_add_tail(&(stu3.list), &score_head);

	list_for_each(pos, &score_head)
	{
		tmp = list_entry(pos, struct score, list);
		printk("Num is %d, English is %d, Math is %d.\n", tmp->num, tmp->english, tmp->math);
	}
    
	return 0;
}

static void __exit chrdev_exit(void)
{
	printk(KERN_DEBUG "chrdev_exit\n");
    
	list_del(&(stu1.list));
	list_del(&(stu2.list));

	list_for_each(pos, &score_head)
	{
		tmp = list_entry(pos, struct score, list);
		printk("Num is %d, English is %d, Math is %d.\n", tmp->num, tmp->english, tmp->math);
	}
}


module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");


