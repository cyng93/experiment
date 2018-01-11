#include <linux/slab.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/limits.h>

struct tagged_obj {
    char obj[NAME_MAX];
    char tag[NAME_MAX];
    struct list_head list;
};

struct tagged_obj tagged_obj_list;


int new_init(void)
{
    struct tagged_obj *new_tagged_obj, *a_tagged_obj;
    char obj1[] = "obj1";
    char obj2[] = "obj2";
    char obj3[] = "obj3";
    char tag[] = "sensitive";

    // init list head
    INIT_LIST_HEAD(&tagged_obj_list.list);
    printk(KERN_INFO" -> Init list head\n");

    // add entry to list
    printk(KERN_INFO" -> Insert into list\n");
    new_tagged_obj = kmalloc(sizeof(*new_tagged_obj), GFP_KERNEL);
    strncpy(new_tagged_obj->obj, obj1, NAME_MAX);
    strncpy(new_tagged_obj->tag, tag, NAME_MAX);
    INIT_LIST_HEAD(&new_tagged_obj->list);
    list_add_tail(&(new_tagged_obj->list), &(tagged_obj_list.list));

    // add another entry to list
    new_tagged_obj = kmalloc(sizeof(*new_tagged_obj), GFP_KERNEL);
    strncpy(new_tagged_obj->obj, obj2, NAME_MAX);
    strncpy(new_tagged_obj->tag, tag, NAME_MAX);
    INIT_LIST_HEAD(&new_tagged_obj->list);
    list_add_tail(&(new_tagged_obj->list), &(tagged_obj_list.list));

    // add third entry to list
    new_tagged_obj = kmalloc(sizeof(*new_tagged_obj), GFP_KERNEL);
    strncpy(new_tagged_obj->obj, obj3, NAME_MAX);
    strncpy(new_tagged_obj->tag, tag, NAME_MAX);
    INIT_LIST_HEAD(&new_tagged_obj->list);
    list_add_tail(&(new_tagged_obj->list), &(tagged_obj_list.list));

    // traverse through list and print out each entry
    printk(KERN_INFO" -> Traverse list:\n");
    list_for_each_entry(a_tagged_obj, &tagged_obj_list.list, list){
        printk(KERN_INFO"  - ['%s' ,'%s']\n",
               a_tagged_obj->obj, a_tagged_obj->tag
               );

        // just to show that we can use break in the list_* macro
        if (!strcmp("obj2", a_tagged_obj->obj)){
            printk("matched found, stop traversing\n");
            break;
        }
    }

    return 0;
}

void new_exit(void)
{
    struct tagged_obj *a_tagged_obj, *tmp;

    // delete node and free allocated memory
    printk(" -> Clean up list:");
    list_for_each_entry_safe(a_tagged_obj, tmp, &tagged_obj_list.list, list){
        printk(KERN_INFO"  - freeing node ['%s', '%s']\n",
               a_tagged_obj->obj, a_tagged_obj->tag
               );
        list_del(&a_tagged_obj->list);
        kfree(a_tagged_obj);
    }
}


module_init(new_init);
module_exit(new_exit);


/*Kernel module Comments*/
MODULE_LICENSE("GPL v2");
