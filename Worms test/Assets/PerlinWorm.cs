using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerlinWorm : MonoBehaviour
{
    LineRenderer line;

    [SerializeField, Range(0,1)]
    float noTurnThreshold = 0.2f;

    //[SerializeField]
    //float yNudge = 0.2f;
    
    [SerializeField]
    float upTurnDepth = -5f;
    
    [SerializeField]
    Vector3 wormStartPos, noiseStartPos, noiseVector;

    [SerializeField]
    Vector3 avg;

    [SerializeField]
    Vector3[] angles;

    [SerializeField,Range(0,250)]
    int segments = 35;

    Vector3[] poses;

    [SerializeField]
    float segmentLength = 1;
      
    // Start is called before the first frame update
    void Start()
    {
        line = gameObject.GetComponent<LineRenderer>();

       
    }

    private void SetPositions(Vector3[] poses)
    {
        line.SetPositions(poses);
    }

    private Vector3[] GetPositions()
    {
        Vector3 prevPos = transform.position;
       // Vector3[] noisePoses = new Vector3[segments];
        for (int i = 0; i < segments; i++)
        {

            Vector3 noisePos = noiseStartPos + i*noiseVector;
            Vector3 offset = Vector3.zero;

         

            float threshold = noTurnThreshold;
            float[] noise = new float[3];

            for (int j = 0; j < 3; j++)
            {

                //float noise = (float)NoiseS3D.NoiseCombinedOctaves(noisePos[j],0); // -1 to 1

                noise[j] = Mathf.Clamp01((float)Mathf.PerlinNoise(noisePos[j]+ j*17f, 0)); // -1 to 1
                noise[j] *= 2f;
                noise[j] -= 1f;


                float move;

                if (Mathf.Abs(noise[j]) < threshold) // no move
                {
                    move = 0;
                }
                else
                {
                    move = Mathf.Sign(noise[j]);
                }
                offset[j] = move;
            }

            //if(i > 0 && poses[i-1].y > upTurnDepth)
            //{
            //    offset.y = Mathf.Clamp(offset.y - 1, -1, 0);
            //}

            angles[i] = offset;

            poses[i] = prevPos + offset*segmentLength;

            prevPos = poses[i];
        }
        return poses;
    }

    private void Init()
    {
        line.positionCount = segments;
        // noiseStartPos = new Vector3( 486,47,186 );
        // wormStartPos = new Vector3( 0,0,0 );
        // noiseVector = new Vector3( 1,0,0 ) ;


        noiseStartPos = transform.position;

        poses = new Vector3[segments];
        angles = new Vector3[segments];

        NoiseS3D.seed = 0;

    }

    // Update is called once per frame
    void Update()
    {

        Init();

        Vector3[] poses = GetPositions();

        SetPositions(poses);

        for (int i = 0; i < 3; i++)
        {
            var temp = 0f;
            for (int j = 0; j < segments; j++)
            {
                temp += angles[j][i];
            }
            avg[i] = temp / (float)segments;
        }
    }

    private void OnDrawGizmos()
    {
        //if (poses == null) return;
        //for (int i = 0; i < segments; i++)
        //{
        //    Vector3 pos = poses[i];
        //    Gizmos.DrawLine(pos, pos + angles[i]);
        //}
    }
}
