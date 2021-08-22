    #include <linux/module.h>
    #include <linux/kernel.h>
    #include <linux/fs.h>
    #include <linux/cdev.h>
    #include <linux/device.h>
    #include <linux/uaccess.h>

    static int device_open(struct inode *, struct file *);
    static int device_release(struct inode *, struct file *);
    static ssize_t device_read(struct file *, char *, size_t, loff_t *);
    static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
    char kernelbuff[1024];
    dev_t mydev; // Store major and minor number from alloc_chrdev_region

    MODULE_LICENSE("GPL");

    struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
    };


    int device_open(struct inode *inode, struct file *fp)
    {
    printk("device_open called");
    return 0;
    }

    static int device_release(struct inode *inode, struct file *fp)
    {
    printk("device_release called");
    return 0;
    }

    static ssize_t device_read(struct file *fp, char *ch, size_t sz, loff_t *lofft)
    {
    printk("device_read called");
    //copy_to_user(ch, kernelbuff, 1024);
    return sz;
    }
    static ssize_t device_write(struct file *fp, const char *ch, size_t sz, loff_t *lofft)
    {
    printk("device_write called");
    //copy_from_user(kernelbuff, ch, 50);
    return 1024;
    }

    static int hello_init(void)
    {
      printk("basicchardriver: module initialized");

      /* alloc_chrdev vs register_chrdev
       *
       * register_chrdev or register_chrdev_region: register_* will statically you have to add a major number, which gets alloted.
       * alloc_chrdev or alloc_chrdev_region: alloc_* will dynamically allocate a major and minor number
       *
       * if you specify region, then a range of numbers gets alloted.
       *
       * Also - functions that end in _region (i.e. alloc_chrdev_region and register_chrdev_region) do not call
       * cdev_alloc at all (so the driver has to call cdev_alloc or cdev_init), whereas register_chrdev and __register_chrdev
       * do call cdev_alloc (so the driver does not need to do so)
       */


      //if (register_chrdev(500, "chr_device", &fops)<0)              // Static allocation. cdev_init / cdev_alloc called
      if (register_chrdev_region(490, 5, "chr_dev_region11")<0)    // Static allocation. cdev_init / cdev_alloc called
      //if (alloc_chrdev_region(&mydev, 0, 5, "my_chr_dev_region")<0) // Dynamic allocation. cdev_init / cdev_alloc NOT called. So driver needs to call
      {
              printk("register: Allocation failed");
      }

      //printk("Major number: %u, Minor number: %u", MAJOR(mydev), MINOR(mydev)); // Uncomment only in case of dynamic-allocation.
      return 0;
    }

    static void hello_exit(void)
    {
      printk("basicchardriver: module exited");
      //unregister_chrdev(490, "chr_device");

      unregister_chrdev_region(238, 5);
    }

    module_init(hello_init);
    module_exit(hello_exit);
