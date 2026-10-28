$res = Invoke-RestMethod -Uri "https://api.github.com/repos/tkietn24-creator/reiman-prime-ios/actions/runs/40670402921/jobs"
$jobId = $res.jobs[0].id
Write-Host "JobID: $jobId"

$log = (Invoke-WebRequest -Uri "https://api.github.com/repos/tkietn24-creator/reiman-prime-ios/actions/jobs/$jobId/logs" -MaximumRedirection 5).Content
$log | Out-File -FilePath "C:\Users\Admin\Downloads\REIMAN PRIME\build_log.txt"

Get-Content "C:\Users\Admin\Downloads\REIMAN PRIME\build_log.txt" | Select-String -Pattern "error:|fatal error:|build_mac.sh" -Context 3,5
