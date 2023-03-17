using System;
using System.Runtime.CompilerServices;

namespace Overlook
{
    public static class InternalCalls
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Entity_HasComponent(ulong entityID, Type componentType);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static ulong Entity_FindEntityByName(string name);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static object GetScriptInstance(ulong entityID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_GetTranslation(ulong entityID, out Vector3 translation);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void TransformComponent_SetTranslation(ulong entityID, ref Vector3 translation);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody2DComponent_ApplyLinearImpulse(ulong entityID, ref Vector2 impulse, ref Vector2 point, bool wake);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(ulong entityID, ref Vector2 impulse, bool wake);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody3DComponent_GetLinearVelocity(ulong entityID, out Vector2 linearVelocity);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody3DComponent_ApplyLinearImpulse(ulong entityID, ref Vector3 impulse, bool wake);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody3DComponent_ApplyAngularVelocityImpulse(ulong entityID, ref Vector3 impulse, bool wake);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static Rigidbody3DComponent.BodyType Rigidbody3DComponent_GetType(ulong entityID);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody3DComponent_SetType(ulong entityID, Rigidbody3DComponent.BodyType type);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Input_IsKeyDown(KeyCode keycode);
    }
}