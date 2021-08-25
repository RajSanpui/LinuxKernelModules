
Char Driver Creation Steps
----------------------------

Step 1. Dynamically allocate a device number 
---------------------------------------------

     ret = alloc_chrdev_region(&device_number,0,1,"pcd_devices");
     if(ret < 0){
        pr_err("Alloc chrdev failed\n");
        goto out;
     }
     pr_info("Device number <major>:<minor> = %d:%d\n",MAJOR(device_number),MINOR(device_number));


     raj@raj:~/ldd/charDriver$ cat /proc/devices
       Character devices:
          238 pcd_devices



Step 2. Associate with file_operations 
---------------------------------------
       cdev_init(&pcd_cdev,&pcd_fops);


Step 3. Register a device (cdev structure) with VFS (Can be done at end as well for activating device)
----------------------------------------------------

      pcd_cdev.owner = THIS_MODULE;
      ret = cdev_add(&pcd_cdev,device_number,1);
      if(ret < 0){
         pr_err("Cdev add failed\n");
         goto unreg_chrdev;
      }



Step 4. Create the device under /sys/class */
---------------------------------------------- 
       
    class_pcd = class_create(THIS_MODULE,"pcd_class");
    if (IS_ERR(class_pcd)){
        pr_err("Class creation failed\n");
        ret = PTR_ERR(class_pcd);
        goto cdev_del;
    }

    raj@raj:/sys/class$ ls -l pcd_class
    total 0
    lrwxrwxrwx 1 root root 0 Aug 25 18:09 pcd -> ../../devices/virtual/pcd_class/pcd


Step 5. Create the device under /dev (as below /dev/pcd)
---------------------------------------------------------
        
    device_pcd = device_create(class_pcd,NULL,device_number,NULL,"pcd");
    if(IS_ERR(device_pcd)){
         pr_err("Device create failed\n");
         ret = PTR_ERR(device_pcd);
         goto class_del;
    }

    raj@raj:/dev$ ls -l pcd
    crw------- 1 root root 238, 0 Aug 25 18:01 pcd


Step 6. De-register the driver
------------------------------

    static void __exit pcd_driver_cleanup(void)
    {
        device_destroy(class_pcd,device_number);
        class_destroy(class_pcd);
        cdev_del(&pcd_cdev);
        unregister_chrdev_region(device_number,1);
        pr_info("module unloaded\n");
    }
    


Device number allocation
----------------------------

register_* will do a major number allocation based on hardcoded value you pass. 
alloc_* will do a dynamic allocation. O/S will choose a major number itself.

APIs that ends in "_region" will alocate a range of major and minor numbers. E.g alloc_chrdev_region.


Also functions that end in _region (i.e. alloc_chrdev_region and register_chrdev_region) do not call cdev_init at all (so the driver has to call cdev_alloc or cdev_init).

Whereas register_chrdev and _register_chrdev call cdev_alloc (so the driver does not need to do so).

Example:

      if (register_chrdev(500, "chr_device", &fops)<0)             
      In the above example, cdev_init is called, so we can directly pass file_operations fops argument to it.
      
      
      if (register_chrdev_region(490, 5, "chr_dev_region11")<0) 
      Here cdev_init is not automatically called in case of "region", so the driver has to call cdev_init and pass file_operations argument to it.
      

alloc_chrdev_region
     ret = alloc_chrdev_region(&device_number,0,1,"pcd_devices");
     
     int alloc_chrdev_region(dev_t *dev, unsigned int firstminor,unsigned int count, char *name);


     dev -> The dev_t variable type,which will get the major number that the kernel allocates.
     firstminor -> The first minor number in case you are looking for a series of minor numbers for your driver.
     count -> The number of contiguous set of major numbers that you want to be allocated.
     name -> Name of your device that should be associated with the major numbers. The same name will appear in /proc/devices.
 
