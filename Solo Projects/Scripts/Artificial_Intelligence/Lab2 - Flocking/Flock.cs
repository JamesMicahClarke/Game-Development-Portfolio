using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FullSailAFI.SteeringBehaviors.Core;

namespace FullSailAFI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region Constructors
        public Flock()
        {
            AveragePosition = Vector3.Zero;
            AverageForward = Vector3.Zero;
        }
        #endregion

        #region TODO Suggested helper methods

        private void CalculateAverages()
        {
            Vector3 tempPos = Vector3.Zero;
            Vector3 tempVel = Vector3.Zero;

            
                for (int j = 0; j < Boids.Count; j++)
                {

                    tempPos += Boids[j].Position;
                    tempVel += Boids[j].Velocity;

                }
                
                AveragePosition = tempPos/Boids.Count;
            AverageForward = tempVel/ Boids.Count;
        
            
        }
       

        private Vector3 CalculateAlignmentAcceleration(MovingObject boid)
        {
            Vector3 vec = AverageForward / boid.MaxSpeed;

            if (vec.Length > 1)
            {
                vec.Normalize();
            }
            return vec * AlignmentStrength;
        }

        private Vector3 CalculateCohesionAcceleration(MovingObject boid)
        {
            Vector3 vec = AveragePosition - boid.Position;
            float distance = vec.Length;
            vec.Normalize();

            if (distance < FlockRadius)
            {
                vec *= distance / FlockRadius;
            }

            return vec * CohesionStrength;
        }

        private Vector3 CalculateSeparationAcceleration(MovingObject boid)
        {
            Vector3 sum = Vector3.Zero;

            for (int i = 0; i < Boids.Count; i++)
            {
                Vector3 vec = boid.Position - Boids[i].Position;
                float distance = vec.Length;
                float safeDist = boid.SafeRadius + Boids[i].SafeRadius;

                if (distance < safeDist)
                {
                    vec.Normalize();
                    vec *= (safeDist - distance) / safeDist;

                    sum += vec;
                }
            }

            if (sum.Length > 1)
                sum.Normalize();

            return sum * SeparationStrength;
        }

        #endregion

        #region TODO

        public virtual void Update(float deltaTime)
        {
           CalculateAverages();

            Vector3 sum = Vector3.Zero;
            for (int i = 0; i < Boids.Count; i++)
            {
                sum = CalculateAlignmentAcceleration(Boids[i]);
                sum += CalculateCohesionAcceleration(Boids[i]);
                sum += CalculateSeparationAcceleration(Boids[i]);

                sum *= Boids[i].MaxSpeed * deltaTime;

                Boids[i].Velocity += sum;

                if (Boids[i].Velocity.Length > Boids[i].MaxSpeed)
                {
                    Boids[i].Velocity.Normalize();
                    Boids[i].Velocity *= Boids[i].MaxSpeed;
                }
                Boids[i].Update(deltaTime);
            }
        }
        #endregion
    }
}
