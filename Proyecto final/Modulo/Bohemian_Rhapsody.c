#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Angel");
MODULE_DESCRIPTION("Farrokh Bulsara");
MODULE_VERSION("0.01");


#define DEVICE_NAME "Bohemian_Rhapsody"

static int major;
struct cdev char_device;

static int Bohemian_Rhapsody_open(struct inode*, struct file*);
static int Bohemian_Rhapsody_release(struct inode*, struct file*);
static ssize_t Bohemian_Rhapsody_read(struct file*, char*, size_t, loff_t*);
static ssize_t Bohemian_Rhapsody_write(struct file*, const char*, size_t, loff_t*);
int write_to_user(char *, char *);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = Bohemian_Rhapsody_open,
    .release = Bohemian_Rhapsody_release,
    .read = Bohemian_Rhapsody_read,
    .write = Bohemian_Rhapsody_write,
};

char user_message[2000] = "Is this the real life? Is this just fantasy?\nCaught in a landslide, no escape from reality\nOpen your eyes, look up to the skies and see\nI'm just a poor boy, I need no sympathy\nBecause I'm easy come, easy go, little high, little low\nAny way the wind blows doesn't really matter to me, to me\nMama, just killed a man\nPut a gun against his head, pulled my trigger, now he's dead\nMama, life had just begun\nBut now I've gone and thrown it all away\nMama, ooh, didn't mean to make you cry\nIf I'm not back again this time tomorrow\nCarry on, carry on as if nothing really matters\nToo late, my time has come\nSends shivers down my spine, body's aching all the time\nGoodbye, everybody, I've got to go\nGotta leave you all behind and face the truth\nMama, ooh (any way the wind blows)\nI don't wanna die\nI sometimes wish I'd never been born at all\nI see a little silhouetto of a man\nScaramouche, Scaramouche, will you do the Fandango?\nThunderbolt and lightning, very, very frightening me\n(Galileo) Galileo, (Galileo) Galileo, Galileo Figaro, magnifico\nBut I'm just a poor boy, nobody loves me\nHe's just a poor boy from a poor family\nSpare him his life from this monstrosity\nEasy come, easy go, will you let me go?\nبِسْمِ ٱللَّٰهِ\nNo, we will not let you go (let him go)\nبِسْمِ ٱللَّٰهِ\nWe will not let you go (let him go)\nبِسْمِ ٱللَّٰهِ\nWe will not let you go (let me go)\nWill not let you go (let me go)\nNever, never, never, never let me go\nNo, no, no, no, no, no, no\nOh, mamma mia, mamma mia\nMamma mia, let me go\nBeelzebub has a devil put aside for me, for me, for me\nSo you think you can stone me and spit in my eye?\nSo you think you can love me and leave me to die?\nOh, baby, can't do this to me, baby\nJust gotta get out, just gotta get right outta here\nOoh\nOoh, yeah, ooh, yeah\nNothing really matters, anyone can see\nNothing really matters\nNothing really matters to me";

static int __init Bohemian_Rhapsody_init(void) {
    int result;
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ALERT "Bohemian_Rhapsody Module load failed\n");
        return major;
    }

    printk(KERN_INFO "Bohemian_Rhapsody Module has been loaded\n");

    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

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

static void __exit Bohemian_Rhapsody_exit(void) {
    printk(KERN_INFO "Ya no hay rola, removiendo módulo!!\n");
}

static int Bohemian_Rhapsody_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Super Module device opened\n");
   return 0;
}


static ssize_t Bohemian_Rhapsody_write(struct file *filep, const char *buffer,
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
    printk(KERN_INFO "From userland: %s\n", (char *)message);
    return len;
}

static int Bohemian_Rhapsody_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Super Module device closed\n");
   return 0;
}

static ssize_t Bohemian_Rhapsody_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "Is this the real life? Is this just fantasy?\nCaught in a landslide, no escape from reality\nOpen your eyes, look up to the skies and see\nI'm just a poor boy, I need no sympathy\nBecause I'm easy come, easy go, little high, little low\nAny way the wind blows doesn't really matter to me, to me\nMama, just killed a man\nPut a gun against his head, pulled my trigger, now he's dead\nMama, life had just begun\nBut now I've gone and thrown it all away\nMama, ooh, didn't mean to make you cry\nIf I'm not back again this time tomorrow\nCarry on, carry on as if nothing really matters\nToo late, my time has come\nSends shivers down my spine, body's aching all the time\nGoodbye, everybody, I've got to go\nGotta leave you all behind and face the truth\nMama, ooh (any way the wind blows)\nI don't wanna die\nI sometimes wish I'd never been born at all\nI see a little silhouetto of a man\nScaramouche, Scaramouche, will you do the Fandango?\nThunderbolt and lightning, very, very frightening me\n(Galileo) Galileo, (Galileo) Galileo, Galileo Figaro, magnifico\nBut I'm just a poor boy, nobody loves me\nHe's just a poor boy from a poor family\nSpare him his life from this monstrosity\nEasy come, easy go, will you let me go?\nبِسْمِ ٱللَّٰهِ\nNo, we will not let you go (let him go)\nبِسْمِ ٱللَّٰهِ\nWe will not let you go (let him go)\nبِسْمِ ٱللَّٰهِ\nWe will not let you go (let me go)\nWill not let you go (let me go)\nNever, never, never, never let me go\nNo, no, no, no, no, no, no\nOh, mamma mia, mamma mia\nMamma mia, let me go\nBeelzebub has a devil put aside for me, for me, for me\nSo you think you can stone me and spit in my eye?\nSo you think you can love me and leave me to die?\nOh, baby, can't do this to me, baby\nJust gotta get out, just gotta get right outta here\nOoh\nOoh, yeah, ooh, yeah\nNothing really matters, anyone can see\nNothing really matters\nNothing really matters to me";
    int message_len = strlen(message);
    errors = copy_to_user(buffer, message, message_len);
    printk(KERN_INFO "user_message: %s\n", message);
    return errors == 0 ? message_len : -EFAULT;
}


module_init(Bohemian_Rhapsody_init);
module_exit(Bohemian_Rhapsody_exit);



