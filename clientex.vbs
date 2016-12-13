Set iProcessMonitor = WScript.CreateObject("Kupchinskiy.ProcessManagerEx")

Dim bStop
bStop = 0

While bStop = 0
	Dim strInput
	strInput = InputBox("Input name", "Process Manager [Extended] IDispatch Client")

	If strInput = "" Then
		bStop = 1
	ElseIf Not iProcessMonitor.RegisterProcessByName(strInput) Then
		WScript.Echo "Error while registering name: " & iProcessMonitor.LastErrorMsg
	End If
Wend

While True
	WScript.Sleep 2000

	Dim time
	time = FormatDateTime(Now, vbShortTime)

	If Not iProcessMonitor.UpdateStatuses Then
		WScript.Echo "Error while updating statuses: " & iProcessMonitor.LastErrorMsg
		Continue
	End If

	If iProcessMonitor.GetChangedStatusFirst() Then
		WScript.Echo time & " Changed statuses:"
		WScript.Echo time & " ============================"
		WScript.Echo time & " (" & iProcessMonitor.statusPid & "," & iProcessMonitor.statusPname & ") Status: " & iProcessMonitor.status

		While iProcessMonitor.GetChangedStatusNext()
			WScript.Echo time & " (" & iProcessMonitor.statusPid & "," & iProcessMonitor.statusPname & ") Status: " & iProcessMonitor.status
		Wend

		WScript.Echo time & " ============================"
	Else
		WScript.Echo time & " No statuses changed at this time"
	End If
Wend
