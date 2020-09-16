SECTIONS
{
    . = ALIGN(0x8000);
    /* zInit code and data - will be freed after init */
    .zInit :
    {
        __commu_dispatch_table_start = .;
        KEEP (*(.commu.handlers))
        __commu_dispatch_table_end = .;
        . = ALIGN(4);
        __sio_creators_start = .;
        KEEP (*(.sio.creators))
        __sio_creators_end = .;
        __hdf_devices_start = .;
        KEEP (*(.hdf.devices))
        __hdf_devices_end = .;
        __zinitcall_bsp_start = .;
        KEEP (*(.zinitcall.bsp0.init))
        KEEP (*(.zinitcall.bsp1.init))
        KEEP (*(.zinitcall.bsp2.init))
        KEEP (*(.zinitcall.bsp3.init))
        KEEP (*(.zinitcall.bsp4.init))
        __zinitcall_bsp_end = .;
        __zinitcall_device_start = .;
        KEEP (*(.zinitcall.device0.init))
        KEEP (*(.zinitcall.device1.init))
        KEEP (*(.zinitcall.device2.init))
        KEEP (*(.zinitcall.device3.init))
        KEEP (*(.zinitcall.device4.init))
        __zinitcall_device_end = .;
        __zinitcall_core_start = .;
        KEEP (*(.zinitcall.core0.init))
        KEEP (*(.zinitcall.core1.init))
        KEEP (*(.zinitcall.core2.init))
        KEEP (*(.zinitcall.core3.init))
        KEEP (*(.zinitcall.core4.init))
        __zinitcall_core_end = .;
        __zinitcall_sys_service_start = .;
        KEEP (*(.zinitcall.sys.service0.init))
        KEEP (*(.zinitcall.sys.service1.init))
        KEEP (*(.zinitcall.sys.service2.init))
        KEEP (*(.zinitcall.sys.service3.init))
        KEEP (*(.zinitcall.sys.service4.init))
        __zinitcall_sys_service_end = .;
        __zinitcall_sys_feature_start = .;
        KEEP (*(.zinitcall.sys.feature0.init))
        KEEP (*(.zinitcall.sys.feature1.init))
        KEEP (*(.zinitcall.sys.feature2.init))
        KEEP (*(.zinitcall.sys.feature3.init))
        KEEP (*(.zinitcall.sys.feature4.init))
        __zinitcall_sys_feature_end = .;
        __zinitcall_run_start = .;
        KEEP (*(.zinitcall.run0.init))
        KEEP (*(.zinitcall.run1.init))
        KEEP (*(.zinitcall.run2.init))
        KEEP (*(.zinitcall.run3.init))
        KEEP (*(.zinitcall.run4.init))
        __zinitcall_run_end = .;
        __zinitcall_app_service_start = .;
        KEEP (*(.zinitcall.app.service0.init))
        KEEP (*(.zinitcall.app.service1.init))
        KEEP (*(.zinitcall.app.service2.init))
        KEEP (*(.zinitcall.app.service3.init))
        KEEP (*(.zinitcall.app.service4.init))
        __zinitcall_app_service_end = .;
        __zinitcall_app_feature_start = .;
        KEEP (*(.zinitcall.app.feature0.init))
        KEEP (*(.zinitcall.app.feature1.init))
        KEEP (*(.zinitcall.app.feature2.init))
        KEEP (*(.zinitcall.app.feature3.init))
        KEEP (*(.zinitcall.app.feature4.init))
        __zinitcall_app_feature_end = .;
        __zinitcall_test_start = .;
        KEEP (*(.zinitcall.test0.init))
        KEEP (*(.zinitcall.test1.init))
        KEEP (*(.zinitcall.test2.init))
        KEEP (*(.zinitcall.test3.init))
        KEEP (*(.zinitcall.test4.init))
        __zinitcall_test_end = .;
        __zinitcall_exit_start = .;
        KEEP (*(.zinitcall.exit0.init))
        KEEP (*(.zinitcall.exit1.init))
        KEEP (*(.zinitcall.exit2.init))
        KEEP (*(.zinitcall.exit3.init))
        KEEP (*(.zinitcall.exit4.init))
        __zinitcall_exit_end = .;
    }
}
INSERT AFTER .text;

