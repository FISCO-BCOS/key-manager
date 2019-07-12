# Key Manager

Manage data encryption keys for FISCO BCOS nodes.**The version only supports** [FISCO BCOS 2.0](https://fisco-bcos-documentation.readthedocs.io/zh_CN/release-2.0/docs/introduction.html).

## Description

In FISCO BCOS, each agency should run its own key manager service. The key manager is deployed in the internal network to manage its data encryption keys.

In **disk encryption**. The following figure shows how the key manager manages encryption data keys. 

![](docs/imgs/framework.png)

Each node has their own ``` dataKey``` and use ``` dataKey``` to communicate with its encrypted space. A node does not manage its ``` dataKey```. It only has its ``` cipherDataKey```. ``` cipherDatakey``` is the ciphertext of ``` datakey ```encrypted by ``` superKey```.  When the node is booting, it sends ``` cipherDataKey``` to key manager, and key manager decrypts the ``` cipherDataKey```  using ``` superKey ``` and return ``` dataKey``` to the node. The node stores ``` dataKey``` in memory and drop it after the node is shut down.

## How to use

### Clone

```shell
git clone https://github.com/FISCO-BCOS/key-manager.git
```

### Install package

Install

```shell
# In Centos
sudo yum install procps-ng-devel
# In ubuntu
sudo apt-get install libprocps-dev
# In ArchLinux
sudo pacman -S procps-ng
```

### Build

```shell
cd key-manager
mkdir build
cd build

# For Centos
cmake3 .. # Notice: There are ".." behind. 
# cmake3 .. -DBUILD_GM=On  #When building "guomi" key-manager

# For ubuntu
cmake .. # Notice: There are ".." behind. 
# cmake .. -DBUILD_GM=On  #When building "guomi" key-manager

make
#The execution: "key-manager" generated.
```

Note：Use ``` -DBUILD_GM=On ``` to build guomi Key Manager if needed.

### Start

``` shell
./key-manager 31443 123xyz # key-manager <port> <superkeyString>
```

### Check

Print info when successfully started.

```log
[1545471609499] [TRACE] key-manager stared. Port: 31443
```

## License

![](https://img.shields.io/github/license/FISCO-BCOS/key-manager.svg)

All contributions are made under the [GNU General Public License v3](https://www.gnu.org/licenses/gpl-3.0.en.html). See [LICENSE](LICENSE).
