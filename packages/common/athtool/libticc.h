/* avm libticc API header, as far as it's known ..
 *
 * Copyright (C) 2017 - Felix Schmidt
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef _libticch_
#define _libticch_

/*! \defgroup libticc libticc prototypes */
/*! @{ */


/*! Read switch register
 *
 * \param reg	[in]  Register offset
 * \param val	[out] Register value
 *
 * \returns 0 on success, !=0 on error
 */
extern int extSwitchReadAthReg (uint32_t reg, uint32_t *val);

/*! Write switch register
 *
 * \param reg	[in]  Register offset
 * \param val	[in]  Register value
 *
 * \returns 0 on success, !=0 on error
 */
extern int extSwitchWriteAthReg (uint32_t reg, uint32_t val);

/*! Release lock for MDIO (extSwitch functions will block if lock is held)
 *
 * /returns 0 on success, !=0 on error
 */
extern int extSwitchMdioAccessUnLock (void);

/*! Obtain lock for MDIO (extSwitch functions will block if lock is held)
 *
 * /returns 0 on success, !=0 on error
	 */
extern int extSwitchMdioAccessLock (void);

/****************** Internal L2 Switch *****************/

/*! Atom Core switch port */
#define L2SW_ATOM	0 
/*! Media-over-Cable switch port */
#define L2SW_MOCA	1
/*! RGMII0 switch port (to ext switch) */
#define L2SW_RGMII0	2
/*! RGMII1 (unused) */
#define L2SW_RGMII1	3
/*! UDMA0 port */
#define L2SW_UDMA0	5
/*! UDMA1 port */
#define L2SW_UDMA1	6
/*! DOCSIS port */
#define L2SW_DOCSIS	7

/*! Internal L2 port name assignment table */
extern const char L2SWITCH_PortNames[8][7];

/*! Enable internal L2 switch port
 *
 * \param port [in] switch port
 */
extern int L2SWITCH_EnablePort (int port);

/*! Disable internal L2 switch port
 *
 * \param port [in] switch port
 */
extern int L2SWITCH_DisablePort (int port);

/*! Add port to new/existing VLAN
 *
 * \param port   [in] switch port
 * \param vid    [in] VLAN id
 * \param tagged [in] 1 if tagged, 0 if not
 * 
 * \returns 0 on success
 */
extern int L2SWITCH_AddPortToVlan (int port, int vid, int tagged);

/*! Remove port from VLAN
 *
 * \param port [in] switch port
 * \param vid  [in] VLAN id
 * 
 * \returns 0 on success
 */
extern int L2SWITCH_RemovePortFromVlan (int port, int vid);

/*! Set ports PVLAN (UNTESTED)
 *
 * \param port [in] switch port
 * \param vid  [in] VLAN id
 * 
 * \returns 0 on success
 */
extern int L2SWITCH_SetPortNativeVlan (int port, int vid);

/*! Get port statistics
 *
 * The size of the stats array seems to be 14 elements.
 *
 * TODO: Determine the meaning of the elements.
 *
 * \param port	 [in] switch port
 * \param stats  [out] pointer to port statistics.
 * 
 * \returns 0 on success
 */
extern int L2SWITCH_GetPortStats (int port, uint32_t *stats);

/*============================================================================
 * libticc .text segment, unknown API
 * \cond
 */
extern int armcode2str (void);
extern int athMdioBusyWait (void);
extern int avm_shm_check_dbs (void);
extern int COMMONUTILS_file_append (void);
extern int COMMONUTILS_file_copy (void);
extern int COMMONUTILS_file_read (void);
extern int COMMONUTILS_file_write (void);
extern int COMMONUTILS_getMonotonicCurrTimeInMiliSec (void);
extern int COMMONUTILS_getMonotonicCurrTimeInSec (void);
extern int COMMONUTILS_getTimeOffset (void);
extern int COMMONUTILS_print_backtrace (void);
extern int COMMONUTILS_setTimeOffset (void);
extern int dictionary_del (void);
extern int dictionary_dump (void);
extern int dictionary_get (void);
extern int dictionary_hash (void);
extern int dictionary_new (void);
extern int dictionary_set (void);
extern int dictionary_unset (void);
extern int do_arm_backtrace (void);
extern int EVENTMGR_BodyMain (void);
extern int EVENTMGR_GetSyslogAddress (void);
extern int EVENTMGR_Init (void);
extern int EVENTMGR_SetEventError (void);
extern int EVENTMGR_SetStatusChange (void);
extern int EVENTMGR_StartSnmpServ (void);
extern int EVENTMGR_StopSnmpServ (void);
extern int EVMIF_DefaultEventTablesAndMasks (void);
extern int EVMIF_DefaultEventTables (void);
extern int EVMIF_EventSend (void);
extern int EVMIF_ExitEventMgr (void);
extern int EVMIF_GetEventEntryByIndex (void);
extern int EVMIF_GetEventEntryNext (void);
extern int EVMIF_GetEventFilterEntryByIndex (void);
extern int EVMIF_GetEventFilterEntryNext (void);
extern int EVMIF_GetLogEntryByIndex (void);
extern int EVMIF_GetLogEntryNext (void);
extern int EVMIF_GetPriorityEntryByIndex (void);
extern int EVMIF_GetPriorityEntryNext (void);
extern int EVMIF_GetSNMPAgentStatus (void);
extern int EVMIF_GetSyslogServer (void);
extern int EVMIF_GetThrotAdminStatus (void);
extern int EVMIF_GetThrotInhibit (void);
extern int EVMIF_GetThrotInterval (void);
extern int EVMIF_GetThrotThreshold (void);
extern int EVMIF_NotifyEventDecisionPoint (void);
extern int EVMIF_ResetEventMgr (void);
extern int EVMIF_ResetLog (void);
extern int EVMIF_SetEventFilter (void);
extern int EVMIF_SetEventLevel (void);
extern int EVMIF_SetEventMask (void);
extern int EVMIF_SetEventText (void);
extern int EVMIF_SetPriorityMask (void);
extern int EVMIF_SetThrotAdminStatus (void);
extern int EVMIF_SetThrotInterval (void);
extern int EVMIF_SetThrotThreshold (void);
extern int EVMIF_SetZeroEventFlag (void);
extern int EVMIF_StartSnmp (void);
extern int EVMIF_StartSyslog (void);
extern int EVMIF_StdTrapSend (void);
extern int EVMIF_StopSnmp (void);
extern int EVMIF_StopSyslog (void);
extern int extSwitch_CapAllPortCounter (void);
extern int extSwitchCfgPortIngressVlanMode (void);
extern int extSwitch_CfgPortQinQCustomerSideMode (void);
extern int extSwitch_CfgPortQinQProviderResetVlan (void);
extern int extSwitch_CfgPortQinQProviderSetVlan (void);
extern int extSwitch_CfgPortQinQProviderSideMode (void);
extern int extSwitchChangePortDefaultVid (void);
extern int extSwitchDb_AddVlan (void);
extern int extSwitchDb_CfgPortIngressVlanMode (void);
extern int extSwitchDb_CfgPortQinQCustomerSideMode (void);
extern int extSwitchDb_CfgPortQinQProviderSetVlan (void);
extern int extSwitchDb_CfgPortQinQProviderSideMode (void);
extern int extSwitchDb_ChangePortDefaultVid (void);
extern int extSwitchDb_GetIsSwitchInPSM (void);
extern int extSwitchDb_GetLinkMaxSpeed (void);
extern int extSwitchDb_GetPortBmap (void);
extern int extSwitchDb_GetPortDefaultVlanid (void);
extern int extSwitchDb_GetPortEgressMode (void);
extern int extSwitchDb_GetPortEtype (void);
extern int extSwitchDb_GetPortIngressMode (void);
extern int extSwitchDb_GetPortProviderVlan (void);
extern int extSwitchDb_GetPortSchedMode (void);
extern int extSwitchDb_GetPortStatus (void);
extern int extSwitchDb_GetQinQCustomerSide (void);
extern int extSwitchDb_GetSize (void);
extern int extSwitchDb_GetVlanIdStatus (void);
extern int extSwitchDb_InitDB (void);
extern int extSwitchDb_PerPortCfgSchedMode (void);
extern int extSwitchDb_PortEnable (void);
extern int extSwitchDb_ResetSwitch (void);
extern int extSwitchDb_RetrieveAccess (void);
extern int extSwitchDb_SetIsSwitchInPSM (void);
extern int extSwitchDb_SetLinkMaxSpeed (void);
extern int extSwitchDb_SetPortEgressMode (void);
extern int extSwitchDb_VlanDelete (void);
extern int extSwitchDb_VlanPortAdd (void);
extern int extSwitchDb_VlanPortDelete (void);
extern int extSwitchGetExtLinkMaxSpeed (void);
extern int extSwitchGetLinkMaxSpeed (void);
extern int extSwitchGetLinkSpeed (void);
extern int extSwitchGetLinkStatus (void);
extern int extSwitchGetStatusPerLink (void);
extern int extSwitchInit802Dot1qMode (void);
extern int extSwitchInitDb (void);
extern int extSwitchMdioMutexInit (void);
extern int extSwitchPerPortCfgSchedMode (void);
extern int extSwitchPortEnable (void);
extern int extSwitchPrintSwitch (void);
extern int extSwitch_RdMacTable (void);
extern int extSwitchReadPhyPortReg (void);
extern int extSwitchReadPhyReg (void);
extern int extSwitch_ResetAllCountersPerAllPorts (void);
extern int extSwitch_ResetAllCountersPerPort (void);
extern int extSwitchResetSwitch (void);
extern int extSwitchRestoreSwitchConfiguration (void);
extern int extSwitchRetrieveAccess (void);
extern int extSwitchSetLinkMaxSpeed (void);
extern int extSwitchSetPortEgressMode (void);
extern int extSwitchSetSwitchInPSM (void);
extern int extSwitchVlanAdd (void);
extern int extSwitchVlanDelete (void);
extern int extSwitchVlanPortAdd (void);
extern int extSwitchVlanPortDelete (void);
extern int extSwitchVlanTable_GetEntryValues (void);
extern int extSwitchWritePhyPortReg (void);
extern int extSwitchWritePhyReg (void);
extern int GetInteger (void);
extern int GetString (void);
extern int Gim_commandTypeToString (void);
extern int Gim_DumpDB (void);
extern int Gim_GetResponseById (void);
extern int Gim_GetResponseLenById (void);
extern int Gim_NotificationEnable (void);
extern int Gim_notificationModeToString (void);
extern int Gim_NotificationRegister (void);
extern int Gim_NotificationReply (void);
extern int Gim_NotificationSend (void);
extern int Gim_notificationTypeToString (void);
extern int Gim_NotificationUnregister (void);
extern int GPTIMER_cancel_request (void);
extern int GPTIMER_get_remaining (void);
extern int GPTIMER_print_list (void);
extern int GPTIMER_request_icc_message (void);
extern int HAL_ExtSwitchCfgPortIngressVlanMode (void);
extern int HAL_ExtSwitch_CfgPortQinQCustomerSideMode (void);
extern int HAL_ExtSwitch_CfgPortQinQProviderResetVlan (void);
extern int HAL_ExtSwitch_CfgPortQinQProviderSetVlan (void);
extern int HAL_ExtSwitch_CfgPortQinQProviderSideMode (void);
extern int HAL_ExtSwitchChangePortDefaultVid (void);
extern int HAL_ExtSwitchChgSwitchInRestoreFlag (void);
extern int HAL_ExtSwitchGetExtLinkMaxSpeed (void);
extern int HAL_ExtSwitchGetLinkMaxSpeed (void);
extern int HAL_ExtSwitchGetLinkSpeed (void);
extern int HAL_ExtSwitchGetLinkStatus (void);
extern int HAL_ExtSwitchGetStatusPerLink (void);
extern int HAL_ExtSwitchInit802Dot1qMode (void);
extern int HAL_ExtSwitchInitDB (void);
extern int HAL_ExtSwitchPerPortCfgSchedMode (void);
extern int HAL_ExtSwitchPortEnable (void);
extern int HAL_ExtSwitchPrintRmon (void);
extern int HAL_ExtSwitchPrintSwitch (void);
extern int HAL_ExtSwitchReadAthReg (void);
extern int HAL_ExtSwitchReadPhyPortReg (void);
extern int HAL_ExtSwitchReadPhyReg (void);
extern int HAL_ExtSwitchResetSwitch (void);
extern int HAL_ExtSwitchRestoreSwitchConfiguration (void);
extern int HAL_ExtSwitchRetrieveAccess (void);
extern int HAL_ExtSwitchSetLinkMaxSpeed (void);
extern int HAL_ExtSwitchSetPortEgressMode (void);
extern int HAL_ExtSwitchSetSwitchInPSM (void);
extern int HAL_ExtSwitchSwitchIGMPSnooping (void);
extern int HAL_ExtSwitchVlanAdd (void);
extern int HAL_ExtSwitchVlanDelete (void);
extern int HAL_ExtSwitchVlanPortAdd (void);
extern int HAL_ExtSwitchVlanPortDelete (void);
extern int HAL_ExtSwitchVlanTable_GetEntryValues (void);
extern int HAL_ExtSwitchWriteAthReg (void);
extern int HAL_ExtSwitchWritePhyPortReg (void);
extern int HAL_ExtSwitchWritePhyReg (void);
extern int ICC_abs_timespec (void);
extern int ICC_alloc_message (void);
extern int ICC_attach_destination_point (void);
extern int ICC_cleanup_pid (void);
extern int ICC_create_destination_point (void);
extern int ICC_data_alloc (void);
extern int ICC_data_free (void);
extern int ICC_data_ptr (void);
extern int ICC_delete_destination_point (void);
extern int ICC_dest_of (void);
extern int ICC_dispose_disable (void);
extern int ICC_dispose_message (void);
extern int ICC_forward_message (void);
extern int ICC_imsg_alloc (void);
extern int ICC_imsg_free (void);
extern int ICC_init (void);
extern int ICC_message_limit (void);
extern int ICC_qelem_alloc (void);
extern int ICC_qelem_free (void);
extern int ICC_reply_message (void);
extern int ICC_send_message_head (void);
extern int ICC_send_message (void);
extern int ICC_set_owner (void);
extern int icc_shminit (void);
extern int ICC_wait_message (void);
extern int imageSignatureGetSignatureOffset (void);
extern int imageSignatureGetSignature (void);
extern int imageSignatureSetSignature (void);
extern int iniparser_dump_ini (void);
extern int iniparser_dump (void);
extern int iniparser_find_entry (void);
extern int iniparser_freedict (void);
extern int iniparser_getboolean (void);
extern int iniparser_getdouble (void);
extern int iniparser_getint (void);
extern int iniparser_getnsec (void);
extern int iniparser_getsecname (void);
extern int iniparser_getstring (void);
extern int iniparser_load (void);
extern int iniparser_set (void);
extern int iniparser_unset (void);
extern int karena_init (void);
extern int kcalloc (void);
extern int kfree (void);
extern int kmalloc (void);
extern int krealloc (void);
extern int L2SWITCH_AddStaticMac (void);
extern int L2SWITCH_DbgDumpCam (void);
extern int L2SWITCH_DbgGetFwDbgData (void);
extern int L2SWITCH_DeleteStaticMac (void);
extern int L2SWITCH_DisableIgmpSnooping (void);
extern int L2SWITCH_EnableIgmpSnooping (void);
extern int L2SWITCH_EnterPsmMode (void);
extern int L2SWITCH_ExitPsmMode (void);
extern int L2SWITCH_GetConfig (void);
extern int L2SWITCH_GetFwLog (void);
extern int L2SWITCH_GetMachState (void);
extern int L2SWITCH_GetMcastMacs (void);
extern int L2SWITCH_GetMcastRouterPorts (void);
extern int L2SWITCH_GetStartupConfig (void);
extern int L2SWITCH_GetUcastMacs (void);
extern int L2SWITCH_InitL2Switch (void);
extern int L2SWITCH_InitLibOnce (void);
extern int L2SWITCH_MdioAccessLock (void);
extern int L2SWITCH_MdioAccessUnlock (void);
extern int L2SWITCH_ReadCbusReg (void);
extern int L2SWITCH_ReadMdio (void);
extern int L2SWITCH_SetEgressLogStatus (void);
extern int L2SWITCH_SetFwLogStatus (void);
extern int L2SWITCH_SetIngressLogStatus (void);
extern int L2SWITCH_SetPortMode (void);
extern int L2SWITCH_SetPortTaggingMode (void);
extern int L2SWITCH_SetStaticMcastRouterPorts (void);
extern int L2SWITCH_StartForwarding (void);
extern int L2SWITCH_StopForwarding (void);
extern int L2SWITCH_WriteCbusReg (void);
extern int L2SWITCH_WriteMdio (void);
extern int lock_freelist (void);
extern int logger_build_send_log_msg (void);
extern int logger_check_file_severity_component_module (void);
extern int logger_check_severity_component_module (void);
extern int logger_disable (void);
extern int logger_enable (void);
extern int logger_get_filename (void);
extern int logger_get_file_size_limit (void);
extern int logger_get_message_queue_limit (void);
extern int logger_get_socket (void);
extern int logger_lib_init (void);
extern int logger_list_components (void);
extern int logger_list_display_format (void);
extern int logger_list_file_components (void);
extern int logger_list_file_module_debug (void);
extern int logger_list_file_modules (void);
extern int logger_list_file_severities (void);
extern int logger_list_module_debug (void);
extern int logger_list_modules (void);
extern int logger_list_severities (void);
extern int logger_list_targets (void);
extern int logger_set_component (void);
extern int logger_set_defaults (void);
extern int logger_set_file_component (void);
extern int logger_set_file_module_debug (void);
extern int logger_set_file_module (void);
extern int logger_set_filename (void);
extern int logger_set_file_severity_level (void);
extern int logger_set_file_size_limit (void);
extern int logger_set_message_display (void);
extern int logger_set_message_output_target (void);
extern int logger_set_message_queue_limit (void);
extern int logger_set_module_debug (void);
extern int logger_set_module (void);
extern int logger_set_severity_level (void);
extern int logger_set_socket (void);
extern int LSD_act_AppCpuRebootStarted (void);
extern int LSD_act_AppCpuUpAndRunning (void);
extern int LSD_act_LsdEvent (void);
extern int LSD_CreateDeviceName (void);
extern int LSD_CreateDevices (void);
extern int LSD_CreateVlanDev (void);
extern int LSD_CreateVlanNP (void);
extern int LSDDB_1LsdOnSwitch0Wlan (void);
extern int LSDDB_ActivateDev (void);
extern int LSDDB_AllocVlanId (void);
extern int LSDDB_CleanVlanIDs (void);
extern int LSDDB_CreateEmpty (void);
extern int LSDDB_DeAllocVlanId (void);
extern int LSDDB_DelDevParams (void);
extern int LSDDB_DevType2Str (void);
extern int LSDDB_Get1stHandleParams (void);
extern int LSDDB_Get1stHandle (void);
extern int LSDDB_GetDevParams (void);
extern int LSDDB_GetFilename (void);
extern int LSDDB_GetHandle (void);
extern int LSDDB_GetNextHandleParams (void);
extern int LSDDB_GetNextHandle (void);
extern int LSDDB_GetSystemFileName (void);
extern int LSDDB_Handle2Section (void);
extern int LSDDB_IsEqHandle (void);
extern int LSDDB_Read (void);
extern int LSDDB_RemoveRt (void);
extern int LSDDB_Section2Handle (void);
extern int LSDDB_SetDevParams (void);
extern int LSDDB_SetFilename (void);
extern int LSDDB_Show (void);
extern int LSDDB_WriteRt (void);
extern int LSDDB_Write (void);
extern int LSD_DeleteVlanNP (void);
extern int LSD_DestroyDevices (void);
extern int LSD_FindAssignTypeinGroupsList (void);
extern int LSD_FreeGroupsList (void);
extern int LSD_InitGroupsList (void);
extern int LSD_InitLsdEvents (void);
extern int LSD_MarkPermanentLSDsUp (void);
extern int LSD_NoSwitch1LsdOnSwitch0Wlan (void);
extern int LSD_togglePowerExtInterface (void);
extern int mstats (void);
extern int NETUTILS_free_igmp6AllInfo (void);
extern int NETUTILS_get_dadResult (void);
extern int NETUTILS_get_igmp6AllInfo (void);
extern int NETUTILS_get_igmp6Entry (void);
extern int NETUTILS_get_inet6IpAddr (void);
extern int NETUTILS_get_linkLocalAddr (void);
extern int NETUTILS_get_mcastGroupAddr (void);
extern int NETUTILS_get_ni_params (void);
extern int NETUTILS_get_ni_stats (void);
extern int NETUTILS_get_routerAdvGw (void);
extern int NETUTILS_get_routerAdvResult (void);
extern int NETUTILS_get_solicitedNodeMacAddr (void);
extern int NETUTILS_set_br_params (void);
extern int NETUTILS_set_ni_params6 (void);
extern int NETUTILS_set_ni_params (void);
extern int NETUTILS_set_route (void);
extern int NVM_AVM_LogGetPrevious (void);
extern int NVM_cleanup (void);
extern int NVM_commit (void);
extern int NVM_end (void);
extern int NVM_get_directly (void);
extern int NVM_get (void);
extern int nvm_init_shm (void);
extern int NVM_LogCyclicAppend (void);
extern int NVM_LogDeleteLastRead (void);
extern int NVM_LogGetFirst (void);
extern int NVM_LogGetLast (void);
extern int NVM_LogGetNext (void);
extern int NVM_LogInit (void);
extern int NVM_LogIsFull (void);
extern int NVM_LogReset (void);
extern int NVM_LogUpdateLastRead (void);
extern int NVM_LogUpdateLast (void);
extern int NVM_set_directly (void);
extern int NVM_set (void);
extern int PCD_api_find_process_id (void);
extern int PCD_api_get_rule_state (void);
extern int PCD_api_kill_process (void);
extern int PCD_api_reboot (void);
extern int PCD_api_reduce_net_rx_priority (void);
extern int PCD_api_register_exception_handlers (void);
extern int PCD_api_restore_net_rx_priority (void);
extern int PCD_api_send_process_ready (void);
extern int PCD_api_signal_process (void);
extern int PCD_api_start_process (void);
extern int PCD_api_terminate_process_non_blocking (void);
extern int PCD_api_terminate_process (void);
extern int pcdwritecrashinfo (void);
extern int pcdwriterebootreason (void);
extern int ProdDb_GetBaudRate (void);
extern int ProdDb_GetBoardConfiguration (void);
extern int ProdDb_GetBTopTable (void);
extern int ProdDb_GetCerFileEuro (void);
extern int ProdDb_GetCerFileUs (void);
extern int ProdDb_GetCmMacAddress (void);
extern int ProdDb_GetDocsisPhyMultFact (void);
extern int ProdDb_GetExtendedUSPower (void);
extern int ProdDb_GetExtRngHoldOffClassId (void);
extern int ProdDb_GetFrequencyPlan (void);
extern int ProdDb_GetHostIpAddr (void);
extern int ProdDb_getHwModel (void);
extern int ProdDb_GetIfName (void);
extern int ProdDb_GetKeyFileEuro (void);
extern int ProdDb_GetKeyFileUs (void);
extern int ProdDb_GetL2SwMacAddr (void);
extern int ProdDb_GetLanIpAddr (void);
extern int ProdDb_GetLanIpMask (void);
extern int ProdDb_GetLanMacAddr (void);
extern int ProdDb_GetMfgOrgNameAndLength (void);
extern int ProdDb_GetMibLevelAccess (void);
extern int ProdDb_GetMTTunerMode (void);
extern int ProdDb_GetNumberOfTunerse (void);
extern int ProdDb_GetPbHwPatch (void);
extern int ProdDb_GetPbHwRevAndPatch (void);
extern int ProdDb_GetPbHwRevision (void);
extern int ProdDb_GetPgaType (void);
extern int ProdDb_GetPhyRegs (void);
extern int ProdDb_GetProductionDate (void);
extern int ProdDb_GetPuma6CancelHsifPumaToTunerCrossInMxl265_7 (void);
extern int ProdDb_GetPuma6UsDACMode (void);
extern int ProdDb_GetPuma6UsFreqRangeMode (void);
extern int ProdDb_GetRev1Default (void);
extern int ProdDb_GetRootPublicLen (void);
extern int ProdDb_GetRootPublicValid (void);
extern int ProdDb_getSerialNumber (void);
extern int ProdDb_GetSerialNumber (void);
extern int ProdDb_getSwVersion (void);
extern int ProdDb_GetTunerModel (void);
extern int ProdDb_GetTunerType (void);
extern int ProdDb_IsBoard958rev2 (void);
extern int ProdDb_SetBaudRate (void);
extern int ProdDb_SetBoardConfiguration (void);
extern int ProdDb_SetBTopTable (void);
extern int ProdDb_SetCerFileEuro (void);
extern int ProdDb_SetCerFileUs (void);
extern int ProdDb_SetCmMacAddress (void);
extern int ProdDb_SetDocsisPhyMultFact (void);
extern int ProdDb_SetExtendedUSPower (void);
extern int ProdDb_SetExtRngHoldOffClassId (void);
extern int ProdDb_SetFrequencyPlan (void);
extern int ProdDb_SetHostIpAddr (void);
extern int ProdDb_SetIfName (void);
extern int ProdDb_SetKeyFileEuro (void);
extern int ProdDb_SetKeyFileUs (void);
extern int ProdDb_SetL2SwMacAddr (void);
extern int ProdDb_SetLanIpAddr (void);
extern int ProdDb_SetLanIpMask (void);
extern int ProdDb_SetLanMacAddr (void);
extern int ProdDb_SetMfgOrgNameAndLength (void);
extern int ProdDb_SetMibLevelAccess (void);
extern int ProdDb_SetMTTunerMode (void);
extern int ProdDb_SetNumberOfTunerse (void);
extern int ProdDb_SetPbHwPatch (void);
extern int ProdDb_SetPbHwRevision (void);
extern int ProdDb_SetPgaType (void);
extern int ProdDb_SetPhyRegs (void);
extern int ProdDb_SetProductionDate (void);
extern int ProdDb_SetPuma6CancelHsifPumaToTunerCrossInMxl265_7 (void);
extern int ProdDb_SetPuma6UsDACMode (void);
extern int ProdDb_SetPuma6UsFreqRangeMode (void);
extern int ProdDb_SetRev1Default (void);
extern int ProdDb_SetRootPublicLen (void);
extern int ProdDb_SetRootPublicValid (void);
extern int ProdDb_SetSerialNumber (void);
extern int ProdDb_SetTunerModel (void);
extern int ProductionDb_Init (void);
extern int ProductionDb_RestoreDBFromNvram (void);
extern int ProductionDb_RetrieveAccess (void);
extern int ProductionDb_SaveToNvram (void);
extern int semcnt (void);
extern int sem_get (void);
extern int sem_mk (void);
extern int sem_PV_TO (void);
extern int sem_PV (void);
extern int sem_rm (void);
extern int send_generic (void);
extern int send_non_srn (void);
extern int send_register (void);
extern int send_srn (void);
extern int shm_create (void);
extern int shm_deinit (void);
extern int shm_get (void);
extern int shm_init (void);
extern int SNMPAIF_AddSocketEntry (void);
extern int SNMPAIF_AVM_GetOidValue (void);
extern int SNMPAIF_CloseAgent (void);
extern int SNMPAIF_DelSocketEntry (void);
extern int SNMPAIF_EngineGetMyBoots (void);
extern int SNMPAIF_EngineGetMyId (void);
extern int SNMPAIF_EngineGetMyTime (void);
extern int SNMPAIF_EngineSetMyInfo (void);
extern int SNMPAIF_GetOidValue (void);
extern int SNMPAIF_ModSocketEntry (void);
extern int SNMPAIF_ReadConfig (void);
extern int SNMPAIF_SendNotify (void);
extern int SNMPAIF_SendUserRequest (void);
extern int SNMPAIF_SetConfig (void);
extern int SNMPAIF_SetTLV11Config (void);
extern int SNMPAIF_SetTLV64Config (void);
extern int SNMPAIF_StartAgent (void);
extern int SNMPAIF_StartSocketEntry (void);
extern int SNMPAIF_StopAgent (void);
extern int SNMPAIF_StopSocketEntry (void);
extern int SNMPIF_AddTarget (void);
extern int SNMPIF_DeleteTarget (void);
extern int SNMPIF_Show (void);
extern int SNMPIF_TargetShow (void);
extern int STARTUP_GetAutoStart (void);
extern int STARTUP_GetDocsisEnabled (void);
extern int STARTUP_GetFilename (void);
extern int STARTUP_RestoreDefaults (void);
extern int STARTUP_SetAutoStart (void);
extern int STARTUP_SetDocsisEnabled (void);
extern int STARTUP_SetFilename (void);
extern int SWT_act_SwtEvent (void);
extern int SWT_ConnectVlan (void);
extern int SWT_CreateLsdVlans (void);
extern int SWT_CreateVlan (void);
extern int SWT_DestroyLsdVlans (void);
extern int SWT_DestroyVlan (void);
extern int SWT_DisonnectVlan (void);
extern int SWT_EnableL2swExtSwitchPort (void);
extern int SWT_EnablePort (void);
extern int SWT_extsw_vlan_add (void);
extern int SWT_extsw_vlan_del (void);
extern int SWT_GetResponseTimeOut (void);
extern int SWT_InitPorts (void);
extern int SWT_IsSwitch (void);
extern int SWT_port_on_extswitch (void);
extern int SWT_ResetSwitch (void);
extern int SWT_SetResponseTimeOut (void);
extern int SWT_vlan_add_port (void);
extern int SWT_vlan_delete_port (void);
extern int TlvParseGeneric (void);
extern int TrimWhiteSpace (void);
extern int unlock_freelist (void);
extern int UPGRADEBOX_CEFDK_ProgramImage (void);
extern int UPGRADEBOX_CEFDK_UploadImage (void);
extern int UPGRADEBOX_File_ClosePartition (void);
extern int UPGRADEBOX_File_Copy (void);
extern int UPGRADEBOX_File_MtdErase (void);
extern int UPGRADEBOX_File_MtdInfo (void);
extern int UPGRADEBOX_File_OpenPartition (void);
extern int UPGRADEBOX_File_Read (void);
extern int UPGRADEBOX_File_Write (void);
extern int UPGRADEBOX_NC_Upload (void);
extern int UPGRADEBOX_Plat_Get_CefdkOffset (void);
extern int UPGRADEBOX_Plat_GetFlashType (void);
extern int UPGRADEBOX_Plat_GetImagePath (void);
extern int UPGRADEBOX_Plat_Get_NPOnly_Mode (void);
extern int UPGRADEBOX_Plat_GetSocType (void);
extern int UPGRADEBOX_Plat_IsAepActive (void);
extern int UPGRADEBOX_TFTP_Download (void);
extern int UPGRADEBOX_ubfiImage_GetImageBaseOffset (void);
extern int UPGRADEBOX_ubfiImage_GetImagesArray (void);
extern int UPGRADEBOX_ubfiImage_GetImageSize (void);
extern int UPGRADEBOX_ubfiImage_GetTotalImageSize (void);
extern int UPGRADEBOX_ubfiImage_Verifiy (void);
extern int UPGRADEBOX_Ubfi_ProgramNpCPU (void);
extern int UPGRADEBOX_uImage_GetImagePartCRC (void);
extern int UPGRADEBOX_uImage_GetImagePartSize (void);
extern int UPGRADEBOX_uImage_GetImagePartType (void);
extern int UPGRADEBOX_uImage_GetImageTotalSize (void);
extern int UPGRADEBOX_uImage_GetName (void);
extern int UPGRADEBOX_uImage_GetNumOfImages (void);
extern int UPGRADEBOX_uImage_GetTimeDate (void);
extern int UPGRADEBOX_uImage_GetVersion (void);
extern int UPGRADEBOX_uImage_Verifiy (void);
extern int UPGRADEBOX_UIMG_ProgramAppCpuImage (void);
extern int UPGRADEBOX_UIMG_ProgramMainImage (void);
extern int UPGRADEBOX_WGET_Download (void);
extern int Util_Snmp_AsnLenBytes (void);
extern int Util_Snmp_AsnLen (void);
extern int Util_Snmp_ConvertASN1Time2Oct (void);
extern int Util_SNMP_ConvertBer2Oid (void);
extern int Util_Snmp_ConvertIp2Oid (void);
extern int Util_Snmp_ConvertOct2UTC (void);
extern int Util_Snmp_ConvertOctet2Oid (void);
extern int Util_Snmp_ConvertOid2Ip (void);
extern int Util_Snmp_ConvertOid2Octet (void);
extern int Util_SNMP_ConvertTlv2Oid (void);
extern int Util_Snmp_ConvertUTC2Oct (void);
extern int Util_Snmp_DisplayString (void);
extern int Util_SNMP_GetLexicOIDNext (void);
extern int Util_Snmp_IsCharIndex (void);
extern int Util_Snmp_IsDateAndTime (void);
extern int Util_Snmp_IsLongIndex (void);
extern int Util_Snmp_IsShortIndex (void);
extern int Util_Snmp_IsUShortIndex (void);
extern int Util_Snmp_ObjIdCmp (void);
extern int Util_Snmp_OidCmp (void);
extern int VEN_SWT_InitSwitch (void);
extern int VEN_WLAN_ConfigWlan (void);
extern int VEN_WLAN_GetWlanPlatformIndex (void);
extern int WLAN_Restart (void);
extern int WLAN_Start (void);
extern int WLAN_Stop (void);
extern int xaddr2str (void);

/* \endcond */

#endif
/*! @} */
