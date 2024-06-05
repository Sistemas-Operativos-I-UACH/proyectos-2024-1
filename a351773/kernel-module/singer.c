#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Damiánm López");
MODULE_DESCRIPTION("This module sings for you");
MODULE_VERSION("0.01");


#define DEVICE_NAME "singermodule"

static int major;
struct cdev char_device;

static int singer_open(struct inode*, struct file*);
static int singer_release(struct inode*, struct file*);
static ssize_t singer_read(struct file*, char*, size_t, loff_t*);
static ssize_t singer_write(struct file*, const char*, size_t, loff_t*);
int write_to_user(char *, char *);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = singer_open,
    .release = singer_release,
    .read = singer_read,
    .write = singer_write,
};

char user_message[1024] = "I don't wanna go back\nNobody's gonna push me off-track, uh huh\nI see what they do\nGood people've got something to lose, uh huh";

static int __init singer_init(void) {
    //int result;
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ALERT "Singer Module load failed\n");
        return major;
    }

    printk(KERN_INFO "Singer Module has taken the stage!\n");
    printk(KERN_INFO "The singer's major number is %d.\n", major);

    /*cdev_init(&char_device, &fops);
    char_device.owner = THIS_MODULE;
    // Add the character device to the system
    result = cdev_add(&char_device, major, 1);
    if (result < 0) {
        unregister_chrdev_region(major, 1);
        pr_err("Failed to add the character device\n");
        return result;
    }

    printk(KERN_INFO "The device file for ths module is: /dev/%s\n", DEVICE_NAME);
    */
    return 0;
}

static void __exit singer_exit(void) {
    printk(KERN_INFO "Goodnight, [your town]! We love you!'\n");
}

static int singer_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Opened lyrics book for singer module\n");
   return 0;
}


static ssize_t singer_write(struct file *filep, const char *buffer,
                         size_t len, loff_t *offset) {
    //int errors = 0;
    static char message[256] = {0};
    if (copy_from_user(message, (void *)buffer, len))
        return -EFAULT;
    /*if (len > 1024) {
        printk(KERN_INFO "The message must be 1024 bytes or less");
        return -EFAULT;
    }*/
    strcpy(user_message, message);
    printk(KERN_INFO "Audience: %s\n", (char *)message);
    return len;
}

static int singer_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Closed lyrics book for singer module\n");
   return 0;
}

static ssize_t singer_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "It's calling me back, House of Sugar...\nDid they bury me here?\nDaddy don't let 'em put me down, daddy don't let 'em turn me around...\n - I don't wanna go back, nobody's gonna push me off track, uh huh\n - I see what they do, good people got something to lose, uh huh\n - I don't wanna go back, nobody's gonna push me off track, uh huh\n - I don't wanna be this, good people gotta fight to exist, uh huh\n - Uh huh\n - Uh huh\n - Uh huh...\n";
    int message_len = strlen(message);
    errors = copy_to_user(buffer, message, message_len);
    printk(KERN_INFO "user_message: %s\n", message);
    return errors == 0 ? message_len : -EFAULT;
}


module_init(singer_init);
module_exit(singer_exit);



