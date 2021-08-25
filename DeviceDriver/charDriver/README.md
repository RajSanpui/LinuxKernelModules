
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
