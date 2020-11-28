using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerlinWorm : MonoBehaviour
{

    LineRenderer line;

    [SerializeField]
    Vector3 wormStartPos, noiseStartPos, noiseVector;

    [SerializeField]
    Vector4[] angles;

    int segments = 35;

    Vector3[] poses;

    [SerializeField]
    float segmentLength = 1;
      
    // Start is called before the first frame update
    void Start()
    {
        Init();
       
    }

    private void SetPositions(Vector3[] poses)
    {
        line.SetPositions(poses);
    }

    private Vector3[] GetPositions()
    {
        Vector3 prevPos = wormStartPos;
       // Vector3[] noisePoses = new Vector3[segments];
        for (int i = 0; i < segments; i++)
        {

            Vector3 noisePos = noiseStartPos + i*noiseVector;
            Vector3 offset = Vector3.zero;

            float noise = (float)NoiseS3D.NoiseCombinedOctaves(noisePos.x, noisePos.y, noisePos.z); // -1 to 1

            /*
             * https://mathworld.wolfram.com/SpherePointPicking.html
            */


            float theta, phi;

            theta = (noise + 1) * Mathf.PI;
            phi = (noise + 1)

            var theta = noise + 1; //0 to 2
            theta *= Mathf.PI; // 0 to 2pi

            float z = Mathf.Cos(theta);
            float a = Mathf.Sqrt(1 - (z * z));

            offset.x = (a * Mathf.Cos(theta)); 
            offset.z = (a * Mathf.Sin(noise));
            offset.y = z;



            Debug.Assert(Mathf.Abs(offset.magnitude - 1) < 0.1f);
            angles[i] = new Vector4(offset.x,offset.y,offset.z,noise);

            poses[i] = prevPos + offset*segmentLength ;

            prevPos = poses[i];
        }
        return poses;
    }

    private void Init()
    {
        line = gameObject.GetComponent<LineRenderer>();
        line.positionCount = segments;
        noiseStartPos = new Vector3( 486,47,186 );
        wormStartPos = new Vector3( 0,0,0 );
        noiseVector = new Vector3( 1,0,0 ) ;

        poses = new Vector3[segments];
        angles = new Vector3[segments];

        NoiseS3D.seed = 0;

    }

    // Update is called once per frame
    void Update()
    {
        Vector3[] poses = GetPositions();

        SetPositions(poses);
    }

    private void OnDrawGizmos()
    {
        if (poses == null) return;
        for (int i = 0; i < segments; i++)
        {
            Vector3 pos = poses[i];
            Gizmos.DrawLine(pos, pos + angles[i]);
        }
    }
}
