var GenericPlatformCrashContext_8h =
[
    [ "FCrashStackFrame", "structFCrashStackFrame.html", "structFCrashStackFrame" ],
    [ "FThreadStackFrames", "structFThreadStackFrames.html", "structFThreadStackFrames" ],
    [ "FSessionContext", "structFSessionContext.html", "structFSessionContext" ],
    [ "FUserSettingsContext", "structFUserSettingsContext.html", "structFUserSettingsContext" ],
    [ "FGPUBreadcrumbsSharedContext", "structFGPUBreadcrumbsSharedContext.html", "structFGPUBreadcrumbsSharedContext" ],
    [ "FGPUBreadcrumbsSharedContext::FQueueData", "structFGPUBreadcrumbsSharedContext_1_1FQueueData.html", "structFGPUBreadcrumbsSharedContext_1_1FQueueData" ],
    [ "FSharedCrashContext", "structFSharedCrashContext.html", "structFSharedCrashContext" ],
    [ "FCrashContextExtendedWriter", "structFCrashContextExtendedWriter.html", "structFCrashContextExtendedWriter" ],
    [ "FThreadCallStack", "structFThreadCallStack.html", "structFThreadCallStack" ],
    [ "FGPUBreadcrumbCrashData", "structFGPUBreadcrumbCrashData.html", "structFGPUBreadcrumbCrashData" ],
    [ "FGPUBreadcrumbCrashData::FQueueData", "structFGPUBreadcrumbCrashData_1_1FQueueData.html", "structFGPUBreadcrumbCrashData_1_1FQueueData" ],
    [ "FGPUBreadcrumbCrashData::FSerializer", "classFGPUBreadcrumbCrashData_1_1FSerializer.html", "classFGPUBreadcrumbCrashData_1_1FSerializer" ],
    [ "FGenericCrashContext", "structFGenericCrashContext.html", "structFGenericCrashContext" ],
    [ "FGenericMemoryWarningContext", "structFGenericMemoryWarningContext.html", null ],
    [ "FAdditionalCrashContextStack", "structFAdditionalCrashContextStack.html", "structFAdditionalCrashContextStack" ],
    [ "FScopedAdditionalCrashContextProvider", "structFScopedAdditionalCrashContextProvider.html", "structFScopedAdditionalCrashContextProvider" ],
    [ "CR_MAX_COMMANDLINE_CHARS", "GenericPlatformCrashContext_8h.html#ab63e5f3e2acc2e1930d9ad967c3a40a1", null ],
    [ "CR_MAX_DIRECTORY_CHARS", "GenericPlatformCrashContext_8h.html#a8344e387cc52498bf2a076ec735cf01b", null ],
    [ "CR_MAX_DYNAMIC_BUFFER_CHARS", "GenericPlatformCrashContext_8h.html#a3a3a7ac5cb843c6563c7f3ac0a697839", null ],
    [ "CR_MAX_ERROR_MESSAGE_CHARS", "GenericPlatformCrashContext_8h.html#a252f563be42689928783560195487ca5", null ],
    [ "CR_MAX_GENERIC_FIELD_CHARS", "GenericPlatformCrashContext_8h.html#a0410f9e4a751b3b973ca77291aa3606c", null ],
    [ "CR_MAX_GPU_BREADCRUMBS_QUEUES", "GenericPlatformCrashContext_8h.html#a07af03d3ac09a67eee21cd1ddbb87223", null ],
    [ "CR_MAX_GPU_BREADCRUMBS_STRING_CHARS", "GenericPlatformCrashContext_8h.html#a1fcb97c04ba7dd22507d8d8bdea3231c", null ],
    [ "CR_MAX_RICHTEXT_FIELD_CHARS", "GenericPlatformCrashContext_8h.html#a90fdd47830f2278b2e32045a7a291396", null ],
    [ "CR_MAX_STACK_FRAMES", "GenericPlatformCrashContext_8h.html#aa948b9e7e1f03a93eaea3c158f67d99e", null ],
    [ "CR_MAX_SYMBOL_CHARS", "GenericPlatformCrashContext_8h.html#a5c44214c12da9014a303f873df06d300", null ],
    [ "CR_MAX_THREAD_NAME_CHARS", "GenericPlatformCrashContext_8h.html#aa6ec175debf9a62b61e097ad4024eb32", null ],
    [ "CR_MAX_THREADS", "GenericPlatformCrashContext_8h.html#ae6cb11ff7ade1c18a2b398bab0c76ed8", null ],
    [ "UE_ADD_CRASH_CONTEXT_SCOPE", "GenericPlatformCrashContext_8h.html#a5156cb587edee0323eb84aa23106125b", null ],
    [ "WITH_ADDITIONAL_CRASH_CONTEXTS", "GenericPlatformCrashContext_8h.html#af492826e4e69bbb8463326393983d66d", null ],
    [ "ECrashContextType", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415a", [
      [ "Crash", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aa275c74140224026380b29b2412d25121", null ],
      [ "Assert", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aad530f9d1b94f864f2238775b0e19e48c", null ],
      [ "Ensure", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aad7ed161ae096c904818fdee16fa84d56", null ],
      [ "Stall", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aaa0f50ad4a913f4008911c70870d4028b", null ],
      [ "GPUCrash", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aaa002ce4e384e960136edf4359e92648b", null ],
      [ "Hang", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aaab2455e33b8ddb6a9d2d41107a2ed4f6", null ],
      [ "OutOfMemory", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aab498327feeb51430af73e07deac268fd", null ],
      [ "AbnormalShutdown", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aa8a397b13c76c80779fa702aea0356fa7", null ],
      [ "VerseRuntimeError", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aaef3c72a600ef037501559d6b0f846288", null ],
      [ "Max", "GenericPlatformCrashContext_8h.html#a69161531111b37cea6c335e145da415aa6a061313d22e51e0f25b7cd4dc065233", null ]
    ] ],
    [ "ECrashDescVersions", "GenericPlatformCrashContext_8h.html#a960aa8371b6194ba8d4a0a081465d9f5", [
      [ "VER_1_NewCrashFormat", "GenericPlatformCrashContext_8h.html#a960aa8371b6194ba8d4a0a081465d9f5af8eef5467fd487e9c43474ecbd6fdb08", null ],
      [ "VER_2_AddedNewProperties", "GenericPlatformCrashContext_8h.html#a960aa8371b6194ba8d4a0a081465d9f5a7cd329b613de0d5a2b387d849c047723", null ],
      [ "VER_3_CrashContext", "GenericPlatformCrashContext_8h.html#a960aa8371b6194ba8d4a0a081465d9f5a73c458a135efe4aa208aba947ac9ce4e", null ]
    ] ],
    [ "ECrashDumpMode", "GenericPlatformCrashContext_8h.html#a0773364a86a751cc50c083c240fcae83", [
      [ "Default", "GenericPlatformCrashContext_8h.html#a0773364a86a751cc50c083c240fcae83a7a1920d61156abc05a60135aefe8bc67", null ],
      [ "FullDump", "GenericPlatformCrashContext_8h.html#a0773364a86a751cc50c083c240fcae83aae130f8f1fb96fe3686a647e5f6277f4", null ],
      [ "FullDumpAlways", "GenericPlatformCrashContext_8h.html#a0773364a86a751cc50c083c240fcae83a6ebeedb82bfaed46e51ed9bb70fa8fb5", null ]
    ] ],
    [ "ECrashExitCodes", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97f", [
      [ "MonitoredApplicationStillRunning", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97fae4953ad4b642ba7b2ab03cda06dbf6d5", null ],
      [ "MonitoredApplicationExitCodeNotAvailable", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97face5d9da5e157a3be4d07362b4c145127", null ],
      [ "CrashReporterCrashed", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97fa2fb95c594e92a1528fdc1b9d8963d51c", null ],
      [ "CrashHandlerCrashed", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97faaba16664e5de61ef772c79bcc5397a82", null ],
      [ "OutOfProcessReporterExitedUnexpectedly", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97fa04e8b2feb0bc097c38a0273d42a21360", null ],
      [ "CrashDuringStaticInit", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97fad0dfba82ee44b0ece79202d02a569aa2", null ],
      [ "OutOfProcessReporterCheckFailed", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97fafd6af5f06b68a4e19b2f464f9de1c7f1", null ],
      [ "UnhandledEnsure", "GenericPlatformCrashContext_8h.html#a64957ec0241defe50da80d011496c97fa19ebda513b56b628d4794d68639247b5", null ]
    ] ],
    [ "ECrashTrigger", "GenericPlatformCrashContext_8h.html#a00bfaae46bf860028280890775df1e40", [
      [ "Debug", "GenericPlatformCrashContext_8h.html#a00bfaae46bf860028280890775df1e40aa603905470e2a5b8c13e96b579ef0dba", null ],
      [ "Normal", "GenericPlatformCrashContext_8h.html#a00bfaae46bf860028280890775df1e40a960b44c579bc2f6818d2daaf9e4c16f0", null ]
    ] ],
    [ "EUnattendedStatus", "GenericPlatformCrashContext_8h.html#a9f2840efec837c9da431a077c50f3a14", [
      [ "Unknown", "GenericPlatformCrashContext_8h.html#a9f2840efec837c9da431a077c50f3a14a88183b946cc5f0e8c96b2e66e1c74a7e", null ],
      [ "Attended", "GenericPlatformCrashContext_8h.html#a9f2840efec837c9da431a077c50f3a14a41e705090f9e4247fe37dcd18ac57ae9", null ],
      [ "Unattended", "GenericPlatformCrashContext_8h.html#a9f2840efec837c9da431a077c50f3a14a3436c9e1e7a490e19537cf2bc07b01a1", null ]
    ] ],
    [ "AttendedStatusToString", "GenericPlatformCrashContext_8h.html#ae78f9ea2ae0635eef521fdccc740e8ad", null ],
    [ "DECLARE_MULTICAST_DELEGATE", "GenericPlatformCrashContext_8h.html#a5f2f5529456c7db91a108ea667b56db8", null ],
    [ "DECLARE_MULTICAST_DELEGATE", "GenericPlatformCrashContext_8h.html#a3085c90074b04185738192f11ff2f506", null ],
    [ "DECLARE_MULTICAST_DELEGATE_OneParam", "GenericPlatformCrashContext_8h.html#a50716f6638b2ad3b40d3c183ef3461c8", null ],
    [ "DECLARE_MULTICAST_DELEGATE_TwoParams", "GenericPlatformCrashContext_8h.html#ad89169c5276b8a8f2834ad6a36b91f2f", null ],
    [ "DECLARE_MULTICAST_DELEGATE_TwoParams", "GenericPlatformCrashContext_8h.html#a4bebb3bf1161cf6f64876ec42de7ab34", null ],
    [ "RecoveryService::GetRecoveryServerName", "namespaceRecoveryService.html#afada358cb1114369a7d502d5533a510c", null ],
    [ "RecoveryService::MakeSessionName", "namespaceRecoveryService.html#a8d775d276f9a37296130e2001b5d1c47", null ],
    [ "RecoveryService::TokenizeSessionName", "namespaceRecoveryService.html#ae26b452c57f7aaf10abd643a2c9fab3e", null ]
];