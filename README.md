# ExportData 使用方法: #

1. 将项目编译结果ExportData.dll文件 (可以从Release目录里获得) 拷贝至飞狐交易师安装目录的FmlDll文件夹下
2. 启动飞狐交易师, 创建一个技术指标, 代码如下:
<pre><code>
If Category <> C_FUTURES Then
i0:"ExportData@ExportData"();
If Category == C_FUTURES && DataType >= 0 && DataType <= 9 Then
i2:"ExportData@ExportData"(Amount, Settle);
</code></pre>
3. 点击"编译公式", 确认编译成功后退出公式编辑器
4. 在希望导出数据的K线图上加载此公式
导出的数据全部按各种不同的时段整理存放在飞狐交易师安装目录的KTExportData文件夹下
