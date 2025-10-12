using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletController : MonoBehaviour
{
    public float bulletSpeed = 50;

    public TankBase bulletOwner;

    public GameObject bullectEffect;



    void Update()
    {
        this.transform.Translate(Vector3.forward * bulletSpeed * Time.deltaTime);
    }

    void OnTriggerEnter(Collider other)
    {
            //bulletOwnerがまだ存在するかどうかを確認します。
        if (bulletOwner == null || bulletOwner.gameObject == null)
        {
            Destroy(gameObject);
            return;
        }

        if (other.CompareTag("Environment") || other.CompareTag("Player") && bulletOwner.CompareTag("Enemy") ||
            other.CompareTag("Enemy") && bulletOwner.CompareTag("Player"))
        {
            TankBase tankBase = other.GetComponent<TankBase>();
            if (tankBase != null)
            {
                tankBase.GetInjured(bulletOwner);
            }

            if (bullectEffect != null)
            {
                GameObject destoryEffect = Instantiate(bullectEffect, this.transform.position, this.transform.rotation);

                AudioSource effectAudio = destoryEffect.GetComponent<AudioSource>();
                effectAudio.volume = DataManager.Instance.musicData.soundValue;
                effectAudio.mute = !DataManager.Instance.musicData.isOnSound;
            }
            Destroy(this.gameObject);
        }
    }

    public void SetOwner(TankBase owner)
    {
        bulletOwner = owner;
    }
}

