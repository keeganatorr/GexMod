using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace GexLauncher
{
	public class Program
	{

        public struct SECURITY_ATTRIBUTES
        {
            public int nLength;
            public IntPtr lpSecurityDescriptor;
            public int bInheritHandle;
        }

        // This also works with CharSet.Ansi as long as the calling function uses the same character set.
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct STARTUPINFO
        {
            public Int32 cb;
            public string lpReserved;
            public string lpDesktop;
            public string lpTitle;
            public Int32 dwX;
            public Int32 dwY;
            public Int32 dwXSize;
            public Int32 dwYSize;
            public Int32 dwXCountChars;
            public Int32 dwYCountChars;
            public Int32 dwFillAttribute;
            public Int32 dwFlags;
            public Int16 wShowWindow;
            public Int16 cbReserved2;
            public IntPtr lpReserved2;
            public IntPtr hStdInput;
            public IntPtr hStdOutput;
            public IntPtr hStdError;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct PROCESS_INFORMATION
        {
            public IntPtr hProcess;
            public IntPtr hThread;
            public int dwProcessId;
            public int dwThreadId;
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool CreateProcess(
            string lpApplicationName,
            string lpCommandLine,
            ref SECURITY_ATTRIBUTES lpProcessAttributes,
            ref SECURITY_ATTRIBUTES lpThreadAttributes,
            bool bInheritHandles,
            uint dwCreationFlags,
            IntPtr lpEnvironment,
            string lpCurrentDirectory,
            [In] ref STARTUPINFO lpStartupInfo,
            out PROCESS_INFORMATION lpProcessInformation);

        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Ansi)]
        static extern IntPtr LoadLibrary([MarshalAs(UnmanagedType.LPStr)] string lpFileName);

        // Token: 0x06000054 RID: 84
        [DllImport("kernel32.dll")]
        internal static extern uint ResumeThread(IntPtr hThread);

        // Token: 0x0600005A RID: 90
        [DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true)]
        private static extern IntPtr VirtualAllocEx(IntPtr ProcessHandle, IntPtr Address, int Size, uint AllocationType, uint Protect);

        public static IntPtr AllocateMemory(IntPtr Handle, int Size)
        {
            return VirtualAllocEx(Handle, (IntPtr)0, Size, 4096u, 4u);
        }

        // Token: 0x06000058 RID: 88
        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, EntryPoint = "WriteProcessMemory", ExactSpelling = true, SetLastError = true)]
        private static extern bool WriteProcessMemoryString(IntPtr ProcessHandle, IntPtr Address, string Buffer, int Size, ref int NumberOfBytesWritten);

        public static bool WriteString(IntPtr Handle, IntPtr Address, string Text)
        {
            int refnum = 0;
            return WriteProcessMemoryString(Handle, Address, Text, Text.Length, ref refnum);
        }

        // Token: 0x06000050 RID: 80
        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, EntryPoint = "GetModuleHandleA", ExactSpelling = true, SetLastError = true)]
        private static extern IntPtr GetModuleHandle(string ModuleName);

        // Token: 0x0600004F RID: 79
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, ExactSpelling = true)]
        private static extern IntPtr GetProcAddress([In] IntPtr ModuleHandle, [MarshalAs(UnmanagedType.LPStr)][In] string ProcedureName);
        // Token: 0x06000051 RID: 81 RVA: 0x00003C98 File Offset: 0x00001E98
        public static IntPtr GetProcedureAddress(string ModuleName, string ProcedureName)
        {
            IntPtr ModuleHandle = (IntPtr)0;
            bool flag = String.Compare(ModuleName.ToLower(), "Kernel32.dll".ToLower()) == 0;
            if (flag)
            {
                try
                {
                    ModuleHandle = GetModuleHandle("KERNELBASE.DLL");
                    ModuleHandle = GetProcAddress(ModuleHandle, ProcedureName);
                    bool flag2 = ModuleHandle != (IntPtr)0;
                    if (flag2)
                    {
                        return ModuleHandle;
                    }
                }
                catch (Exception ex)
                {
                }
            }
            bool flag3 = ModuleHandle == (IntPtr)0;
            if (flag3)
            {
                ModuleHandle = GetModuleHandle(ModuleName.ToLower());
            }
            ModuleHandle = GetProcAddress(ModuleHandle, ProcedureName);
            return ModuleHandle;
        }


        // Token: 0x0600005E RID: 94
        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        private static extern IntPtr CreateRemoteThread(IntPtr ProcessHandle, int ThreadAttributes, int StackSize, IntPtr StartAddress, int Parameter, int CreationFlags, ref IntPtr ThreadId);

        // Token: 0x0600005F RID: 95 RVA: 0x00003F40 File Offset: 0x00002140
        public static bool Execute(IntPtr Handle, long Address, int Parameter = 0)
        {
            IntPtr intPtr = (IntPtr)0;
            IntPtr result = CreateRemoteThread(Handle, 0, 0, (IntPtr)Address, Parameter, 0, ref intPtr);
            if (result.ToInt64() > 0) return true;
            else return false;
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool WriteProcessMemory(
          IntPtr hProcess,
          IntPtr lpBaseAddress,
          byte[] lpBuffer,
          Int32 nSize,
          out IntPtr lpNumberOfBytesWritten);
        public static bool WriteArray(IntPtr Handle, IntPtr Address, byte[] Bytes)
        {
            IntPtr refnum;
            return WriteProcessMemory(Handle, Address, Bytes, Bytes.Length, out refnum);
        }

        // Token: 0x0600005C RID: 92
        [DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true)]
        private static extern bool VirtualFreeEx(IntPtr ProcessHandle, IntPtr Address, uint Size, uint FreeType);

        // Token: 0x0600005D RID: 93 RVA: 0x00003F08 File Offset: 0x00002108
        public static bool FreeMemory(IntPtr Handle, IntPtr Address)
        {
            byte[] b = new byte[272];
            WriteArray(Handle, Address, b);
            return VirtualFreeEx(Handle, (IntPtr)Address, 0u, 0x00008000);
        }
        // Token: 0x0600004C RID: 76 RVA: 0x00003BD8 File Offset: 0x00001DD8
        public static bool InjectDll(string DLLPath, PROCESS_INFORMATION pInfo)
        {
            IntPtr DLLAddress = AllocateMemory(pInfo.hProcess, DLLPath.Length);
            bool flag = (DLLAddress.ToInt64() != 0);
            if (flag)
            {
                bool flag2 = WriteString(pInfo.hProcess, DLLAddress, DLLPath);
                if (flag2)
                {
                    IntPtr LoadLibraryA = GetProcedureAddress("Kernel32.dll", "LoadLibraryA");
                    bool flag3 = LoadLibraryA != (IntPtr)0;
                    if (flag3)
                    {
                        bool flag4 = Execute(pInfo.hProcess, (long)LoadLibraryA, (int)DLLAddress);
                        if (flag4)
                        {
                            Thread.Sleep(500);
                            bool flag5 = FreeMemory(pInfo.hProcess, DLLAddress);
                            if (flag5)
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }


        static void Main(string[] args)
		{
            
            /*const uint NORMAL_PRIORITY_CLASS = 0x0020;
            const uint IDLE_PRIORITY_CLASS = 0x0040;
            const uint CREATE_SUSPENDED = 0x4;

            bool retValue;
            string Application = @"C:\Users\Keegan\Dropbox\GEX\Gex-GOG\Gex.exe";
            string CurrentDirectory = @"C:\Users\Keegan\Dropbox\GEX\Gex-GOG";
            string CommandLine = @"JAchWieGutDasKeinerWeis";
            PROCESS_INFORMATION pInfo = new PROCESS_INFORMATION();
            STARTUPINFO sInfo = new STARTUPINFO();
            SECURITY_ATTRIBUTES pSec = new SECURITY_ATTRIBUTES();
            SECURITY_ATTRIBUTES tSec = new SECURITY_ATTRIBUTES();
            pSec.nLength = Marshal.SizeOf(pSec);
            tSec.nLength = Marshal.SizeOf(tSec);

            //Open Notepad
            retValue = CreateProcess(Application, CommandLine,
            ref pSec, ref tSec, false, CREATE_SUSPENDED,
            IntPtr.Zero, CurrentDirectory, ref sInfo, out pInfo);

            Console.WriteLine("Process ID (PID): " + pInfo.dwProcessId);
            Console.WriteLine("Process Handle : " + pInfo.hProcess);
            string DLLPath = @"C:\Users\Keegan\source\repos\Gex2021\Debug\Gex2021.dll";

            InjectDll(DLLPath, pInfo);

            ResumeThread(pInfo.hThread);*/
            
            const uint NORMAL_PRIORITY_CLASS = 0x0020;
            const uint IDLE_PRIORITY_CLASS = 0x0040;
            const uint CREATE_SUSPENDED = 0x4;

            bool retValue;
            string Application = @"Gex.exe";
            string CurrentDirectory = Directory.GetCurrentDirectory();;
            string CommandLine = @"JAchWieGutDasKeinerWeis";
            PROCESS_INFORMATION pInfo = new PROCESS_INFORMATION();
            STARTUPINFO sInfo = new STARTUPINFO();
            SECURITY_ATTRIBUTES pSec = new SECURITY_ATTRIBUTES();
            SECURITY_ATTRIBUTES tSec = new SECURITY_ATTRIBUTES();
            pSec.nLength = Marshal.SizeOf(pSec);
            tSec.nLength = Marshal.SizeOf(tSec);

            //Open Notepad
            retValue = CreateProcess(Application, CommandLine,
            ref pSec, ref tSec, false, CREATE_SUSPENDED,
            IntPtr.Zero, CurrentDirectory, ref sInfo, out pInfo);

            Console.WriteLine("Process ID (PID): " + pInfo.dwProcessId);
            Console.WriteLine("Process Handle : " + pInfo.hProcess);
            string DLLPath = $@"{CurrentDirectory}\Gex2021.dll";

            InjectDll(DLLPath, pInfo);

            ResumeThread(pInfo.hThread);
        }
	}
}
