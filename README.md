# Key Manager

Manage keys for FISCO BCOS.

## Description

In FISCO BCOS consortium chain framework, each organization has their own key manager. Organization use key manager to manage their keys. Key manager is deployed in organization's internal network. **The version only supports** [FISCO BCOS 2.0](https://fisco-bcos-documentation.readthedocs.io/zh_CN/release-2.0/docs/introduction.html).


In **disk encryption**. This shows how key manager manages data key for nodes. 

![](docs/imgs/framework.png)

Each node has their own ``` dataKey``` and use ``` dataKey``` to communicate with its encrypted space. Node does not manage its ``` dataKey```. It only has its ``` cipherDataKey```. ``` cipherDatakey``` is the cipher of ``` datakey ```encrypted by ``` superKey```.  When node is booting, it sends ``` cipherDataKey``` to key manager, and key manager decrypts the ``` cipherDataKey```  using ``` superKey ``` and return ``` dataKey``` to node. Node manage ``` dataKey``` in memory and drop it after shutting down.

## How to use

### Clone

``` shell
git clone https://github.com/FISCO-BCOS/key-manager.git
```

### Install package

Install

``` shell
# In Centos
sudo yum install procps-ng-devel
# In ubuntu
sudo apt-get install libprocps-dev
```

### Build

``` shell
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

### Start

``` shell
./key-manager 31443 123xyz # key-manager <port> <superkey>
```

### Check

Print info when successfully started.

``` log
[1545471609499] [TRACE] key-manager stared. Port: 31443
```

## License

![](https://img.shields.io/github/license/FISCO-BCOS/key-manager.svg)

All contributions are made under the [GNU General Public License v3](https://www.gnu.org/licenses/gpl-3.0.en.html). See [LICENSE](LICENSE).
