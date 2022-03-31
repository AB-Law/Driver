#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

//USB Probe
//This function is called when a new device is connected to the system.
//It is called by the USB subsystem when it has found a new device.
//The function is passed a pointer to the usb_device structure for the device.
static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_device *udev = interface_to_usbdev(interface);
    printk(KERN_INFO "USB device %04x:%04x connected\n",
           udev->descriptor.idVendor, udev->descriptor.idProduct);
    return 0;
}

//USB Disconnect
//This function is called when a device is disconnected from the system.
//It is called by the USB subsystem when it has found a device has been removed from the system.
//The function is passed a pointer to the usb_device structure for the device.
static void usb_disconnect(struct usb_interface *interface)
{
    struct usb_device *udev = interface_to_usbdev(interface);
    printk(KERN_INFO "USB device %04x:%04x disconnected\n",
           udev->descriptor.idVendor, udev->descriptor.idProduct);
}

//USB Table
//This is the table of USB devices that this driver supports.
//It is used by the USB subsystem to match devices to this driver.
//The table is an array of usb_device_id structures.
//The USB subsystem will match the device to the first entry in the table that matches the device.
//If no entry in the table matches the device, the driver will not be loaded.
static struct usb_device_id usb_table[] = {
    { USB_DEVICE(0x0781, 0x5567) },
    { }
};
MODULE_DEVICE_TABLE (usb, usb_table);


//Create a skeleton USB driver structure
static struct usb_driver usb_driver = {
    .name = "USB Driver",
    .probe = usb_probe,
    .id_table = usb_table,
    .disconnect = usb_disconnect,
};


//USB_init
//This function is called when the module is loaded.
//It is responsible for registering the driver with the USB subsystem.
static int __init usb_init(void)
{
    int result = usb_register(&usb_driver);
    if (result == 0)
        printk(KERN_INFO "USB driver registered\n");
    else
        printk(KERN_ERR "USB driver registration failed\n");
    return result;
}

//USB_exit  
//This function is called when the module is unloaded.
//It is responsible for unregistering the driver with the USB subsystem.
static void __exit usb_exit(void)
{
    usb_deregister(&usb_driver);
    printk(KERN_INFO "USB driver deregistered\n");
}

module_init(usb_init);
module_exit(usb_exit);

