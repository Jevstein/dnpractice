

#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <linux/inetdevice.h>



#define MAX_ETH_FRAME_SIZE	1600
#define DEF_MSG_ENABLE		0xFFFF

static struct net_device *nic_dev[2];

//tx --> send  rx --> recv
//ether frame 
struct nic_priv {
	unsigned char *tx_buf;
	unsigned int tx_len;

	u32 msg_enable;
};


int	nic_open(struct net_device *dev) {

	struct nic_priv *priv = netdev_priv(dev);
	netif_info(priv, ifup, dev, "%s(#%d), priv:%p\n", __func__, __LINE__, priv);

	priv->tx_buf = kmalloc(MAX_ETH_FRAME_SIZE, GFP_KERNEL);
	if (!priv->tx_buf) {
		netif_info(priv, ifup, dev, "%s(#%d), connot alloc tx buffer\n", __func__, __LINE__);
		return -ENOMEM;
	}

	//request_irq(priv->rx_irq, rx_interrupt, )

	netif_start_queue(dev);

	return 0;	
}

int	nic_stop(struct net_device *dev) {

	
	struct nic_priv *priv = netdev_priv(dev);
	netif_info(priv, ifdown, dev, "%s(#%d), priv:%p\n", __func__, __LINE__, priv);

	if (priv->tx_buf) {
		kfree(priv->tx_buf);
	}

	netif_stop_queue(dev);

	return 0;
}

int	nic_validate_addr(struct net_device *dev) {

	struct nic_priv *priv = netdev_priv(dev);
	netif_info(priv, drv, dev, "%s(#%d), priv:%p\n", __func__, __LINE__, priv);

	return eth_validate_addr(dev);
}

netdev_tx_t nic_start_xmit(struct sk_buff *skb, struct net_device *dev) {
	return NETDEV_TX_OK;
}

int	nic_change_mtu(struct net_device *dev, int new_mtu) {

	struct nic_priv *priv = netdev_priv(dev);
	netif_info(priv, drv, dev, "%s(#%d), priv:%p, mtu: %d\n", __func__, __LINE__, priv, new_mtu);

	return eth_change_mtu(dev, new_mtu);
}

int	nic_set_mac_address(struct net_device *dev, void *addr) {

	return 0;
}


static const struct net_device_ops nic_netdev_ops = {
	.ndo_open = nic_open, //ifconfig eth2 up
	.ndo_stop = nic_stop, //ifconfig eth2 down
	.ndo_validate_addr = nic_validate_addr, //ifconfig eth2 192.168.1.23 up
	.ndo_start_xmit = nic_start_xmit, //send
	.ndo_change_mtu = nic_change_mtu, //ifconfig eth2 mtu 1500 up
	.ndo_set_mac_address = nic_set_mac_address, //ifconfig eth2 hwaddr b2:19:1d:6c:ca:b3 up
};

//----------------

static struct net_device *nic_alloc_netdev(void) {

	struct net_device *netdev = alloc_etherdev(sizeof(struct nic_priv));
	if (!netdev) {
		pr_err("%s(#%d): alloc dev failed\n", __func__, __LINE__);
		return NULL;
	}

	eth_hw_addr_random(netdev);

	netdev->netdev_ops = &nic_netdev_ops;
	netdev->flags |= IFF_NOARP;

	netdev->features |= NETIF_F_HW_CSUM;
	//netdev->header_ops = 

	return netdev;
}

//insmod
static int __init nic_init(void) {

	int ret = 0;
	struct nic_priv *priv;

	pr_info("%s(#%d): install module\n", __func__, __LINE__);	

	nic_dev[0] = nic_alloc_netdev();
	if (!nic_dev[0]) {
		printk("%s(#%d): alloc netdev[0] failed\n", __func__, __LINE__);
		return -ENOMEM;
	}

	nic_dev[1] = nic_alloc_netdev();
	if (!nic_dev[1]) {
		printk("%s(#%d): alloc netdev[1] failed\n", __func__, __LINE__);
		goto alloc_2nd_failed;
	}

	ret = register_netdev(nic_dev[0]);
	if (ret) {
		printk("%s(#%d): register netdev[0] failed\n", __func__, __LINE__);
		goto reg1_failed;
	}

	ret = register_netdev(nic_dev[1]);
	if (ret) {
		printk("%s(#%d): register netdev[1] failed\n", __func__, __LINE__);
		goto reg2_failed;
	}
	
	priv = netdev_priv(nic_dev[0]);
	priv->msg_enable = DEF_MSG_ENABLE; //msg enable, 

	priv = netdev_priv(nic_dev[1]);
	priv->msg_enable = DEF_MSG_ENABLE; //msg enable, 

	return 0;


reg2_failed:
	unregister_netdev(nic_dev[0]);
	
reg1_failed:
	free_netdev(nic_dev[1]);

alloc_2nd_failed:
	free_netdev(nic_dev[0]);

	return ret;
}


//rmmod
static void __exit nic_exit(void) {
	int i = 0;
	pr_info("%s(#%d): remove module\n", __func__, __LINE__);

	for (i = 0;i < ARRAY_SIZE(nic_dev);i ++) {
		unregister_netdev(nic_dev[i]);
		free_netdev(nic_dev[i]);
	}
}


module_init(nic_init);
module_exit(nic_exit);