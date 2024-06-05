#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Irlanda, Danna, Adrian, Luis");
MODULE_DESCRIPTION("Module playing Metallica!");
MODULE_VERSION("0.02");

#define DEVICE_NAME "metallicamodule"

static int major;
struct cdev char_device;

static int metallica_open(struct inode *, struct file *);
static int metallica_release(struct inode *, struct file *);
static ssize_t metallica_read(struct file *, char *, size_t, loff_t *);
static ssize_t metallica_write(struct file *, const char *, size_t, loff_t *);
int copy_to_user_buffer(char *, char *);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = metallica_open,
    .release = metallica_release,
    .read = metallica_read,
    .write = metallica_write,
};

char user_message[2048] = "OUTTA MY WAY\nOUTTA MY DAY\nOUT OF YOUR MIND AND INTO MINE\nINTO NO ONE\nINTO NOT ONE\nINTO YOUR STEP BUT OUT OF TIME\nHEADSTRONG\nWHAT’S WRONG?\nI’VE ALREADY HEARD THIS SONG BEFORE\nYOU ARRIVED, BUT NOW IT’S TIME TO KISS YOUR ASS GOODBYE\nDRAGGING ME DOWN\nWHY YOU AROUND?\nSO USELESS\nIT AIN’T MY FALL\nIT AIN’T MY CALL\nIT AIN’T MY BITCH\nIT AIN’T MY BITCH\nDOWN ON THE SUN\nDOWN AND NO FUN\nDOWN AND OUT, WHERE THE HELL YOU BEEN?\nDAMN IT ALL DOWN\nDAMN IT UNBOUND\nDAMN IT ALL DOWN TO HELL AGAIN\nSTAND TALL\nCAN’T FALL\nNEVER EVEN BEND AT ALL BEFORE\nYOU ARRIVED, BUT NOW IT’S TIME TO KISS YOUR ASS GOODBYE\nDRAGGING ME DOWN\nWHY YOU AROUND?\nSO USELESS\nIT AIN’T MY FALL\nIT AIN’T MY CALL\nIT AIN’T MY BITCH\nOUTTA MY WAY\nOUTTA MY WAY\nOUTTA MY DAY\nOUT OF YOUR MIND AND INTO MINE\nINTO NO ONE\nINTO NOT ONE\nINTO YOUR STEP BUT OUT OF TIME\nHEADSTRONG\nWHAT’S WRONG?\nI’VE ALREADY HEARD THIS SONG BEFORE\nYOU ARRIVED, BUT NOW IT’S TIME TO KISS YOUR ASS GOODBYE\nAND NOW IT’S TIME TO KISS YOUR ASS GOODBYE\nDRAGGING ME DOWN\nWHILE YOU AROUND?\nSO USELESS\nIT AIN’T MY FALL\nIT AIN’T MY CALL\nIT AIN’T MY BITCH\nNO WAY BUT DOWN\nWHY YOU’RE AROUND\nNO FOOLING\nIT AIN’T MY SMILE\nIT AIN’T MY STYLE\nIT AIN’T MY BITCH\nOH, IT AIN’T MINE\nAIN’T MINE\nYOUR KIND\nYOU’RE STEPPING OUT OF TIME\nAIN’T MINE\nYOUR KIND\nYOU’RE STEPPING OUT OF TIME\nTAKING ME DOWN\nWHY YOU AROUND\nNO FOOLING\nIT AIN’T MY FALL\nIT AIN’T MY CALL\nIT AIN’T MY BITCH\nYOU AIN’T MINE\n";

static int __init metallica_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0)
    {
        printk(KERN_ALERT "Metallica Module load failed\n");
        return major;
    }

    printk(KERN_INFO "Metallica Module has been loaded\n");
    printk(KERN_INFO "Assigned major number %d. To interact with\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

    return 0;
}

static void __exit metallica_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Unloading Metallica Module!!\n");
}

static int metallica_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Metallica Module device opened\n");
    return 0;
}

static ssize_t metallica_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    static char message[256] = {0};
    if (copy_from_user(message, buffer, len))
        return -EFAULT;

    strncpy(user_message, message, sizeof(user_message) - 1);
    user_message[sizeof(user_message) - 1] = '\0';
    printk(KERN_INFO "From userland: %s\n", message);
    return len;
}

static int metallica_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Metallica Module device closed\n");
    return 0;
}

static ssize_t metallica_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    int errors = 0;
    int message_len = strlen(user_message);
    if (*offset >= message_len)
    {
        return 0;
    }

    if (len > message_len - *offset)
    {
        len = message_len - *offset;
    }

    errors = copy_to_user(buffer, user_message + *offset, len);
    if (errors == 0)
    {
        *offset += len;
        printk(KERN_INFO "Sent %zu characters to the user\n", len);
        return len;
    }
    else
    {
        printk(KERN_INFO "Failed to send %d characters to the user\n", errors);
        return -EFAULT;
    }
}

module_init(metallica_init);
module_exit(metallica_exit);
