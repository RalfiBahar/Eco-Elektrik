' ----------------------------------------------
' Script generated by SIwave - SI Wizard with Netlist
' Tue Apr 20 08:41:24 2021
' ----------------------------------------------
Dim oAnsoftApp
Dim oDesktop
Dim oProject
Dim oDesign
Dim oModule
Set oAnsoftApp = CreateObject("Ansoft.ElectronicsDesktop.2020.2")
Set oDesktop = oAnsoftApp.GetAppDesktop()
oDesktop.RestoreWindow

Set oProject = oDesktop.OpenProject("C:/Users/guven/Desktop/-AESK-/ALL Documents/Drive Electric 2020/Elektrik/Motor Driver/BLDC Driver/[1] Hardware/[1] Power/Project Outputs for Power/odb/SIWAWE DENEME1.siwaveresults/Designer/SIwizard1.aedt")
Set oDesign = oProject.SetActiveDesign("SIWAWE DENEME1_SIwizard1")

oDesign.Analyze

'CREATE A REPORT FOR RECEIVER INPUT VOLTAGE WAVEFORMS
Set oModule = oDesign.GetModule("ReportSetup")
oModule.CreateReport "Voltage Waveforms at Receivers", "Standard", "Rectangular Plot", "TRAN", Array("NAME:Context", "SimValueContext:=", Array( _
  1, 0, 2, 0, false, false, -1, 1, 0, 1, 1, "", 0, 0, "DE", false, "0", "DP",  _
  false, "20000000", "DT", false, "0.001", "WE", false, "2.5E-08", "WM", false,  _
  "2.5E-08", "WN", false, "0", "WS", false, "0s")), Array("Time:=", Array("All")), Array("X Component:=",  _
  "Time", "Y Component:=", _
  Array( _
  "V(CS_PHASE_B_3_1x3_PIN_PHASE_B)", _
  "V(CS_PHASE_B_3_ACS770LCB-050B-PFF-T_U3)", _
  "V(CS_PHASE_A_3_1x3_PIN_PHASE_A)", _
  "V(CS_PHASE_A_3_ACS770LCB-050B-PFF-T_U1)", _
  "V(CS_PHASE_C_3_1x3_PIN_PHASE_C)", _
  "V(CS_PHASE_C_3_ACS770LCB-050B-PFF-T_U4)"  _
  )), Array()
oProject.Save
