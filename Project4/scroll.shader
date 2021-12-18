Shader "Unlit/scroll"
{

    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        
        _ScrollSpeeds ("Scroll Speeds", vector) = (-25, -20, -25, 0)
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct pos
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;
            float4 _ScrollSpeeds;

            pos vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv - 0.5f;
                UNITY_TRANSFER_FOG(o,o.vertex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                float2 polar = float2(
                atan2(i.uv.y, i.uv.x)/(2.0f * 3.141592653589f), length(i.uv)                                    


                );
                
                polar * = _MainTex_ST.xy;
                polar + = _ScrollSpeeds.xy * _Time.x;
                fixed4 col = tex2D(_MainTex, polar);
                
                
                UNITY_APPLY_FOG(i.fogCoord, col);
                return col;
            }
            ENDCG
        }
    }
} //I copied some of DMGregory♦'s code from StackExchange.
