
using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Overlook
{
    public class Input
    {
        public static bool IsKeyDown(KeyCode keycode)
        {
            return InternalCalls.Input_IsKeyDown(keycode);
        }
    }
}