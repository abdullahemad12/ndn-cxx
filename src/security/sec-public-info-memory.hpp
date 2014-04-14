/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#ifndef NDN_SECURITY_SEC_PUBLIC_INFO_MEMORY_HPP
#define NDN_SECURITY_SEC_PUBLIC_INFO_MEMORY_HPP

#include "../common.hpp"
#include "sec-public-info.hpp"

namespace ndn {

/**
 * @brief SecPublicInfoMemory extends SecPublicInfo and implements its methods to store identity, public key and certificate objects in memory.
 */
class SecPublicInfoMemory : public SecPublicInfo {
public:
  class Error : public SecPublicInfo::Error
  {
  public:
    explicit
    Error(const std::string& what)
      : SecPublicInfo::Error(what)
    {
    }
  };

  virtual
  ~SecPublicInfoMemory();

  virtual bool
  doesIdentityExist(const Name& identityName);

  virtual void
  addIdentity(const Name& identityName);

  virtual bool
  revokeIdentity();

  virtual bool
  doesPublicKeyExist(const Name& keyName);

  virtual void
  addPublicKey(const Name& keyName, KeyType keyType, const PublicKey& publicKeyDer);

  virtual ptr_lib::shared_ptr<PublicKey>
  getPublicKey(const Name& keyName);

  virtual bool
  doesCertificateExist(const Name& certificateName);

  virtual void
  addCertificate(const IdentityCertificate& certificate);

  virtual ptr_lib::shared_ptr<IdentityCertificate>
  getCertificate(const Name& certificateName);


  virtual Name
  getDefaultIdentity();

  virtual Name
  getDefaultKeyNameForIdentity(const Name& identityName);

  virtual Name
  getDefaultCertificateNameForKey(const Name& keyName);

  virtual void
  getAllIdentities(std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllKeyNames(std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllKeyNamesOfIdentity(const Name& identity, std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllCertificateNames(std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllCertificateNamesOfKey(const Name& keyName, std::vector<Name>& nameList, bool isDefault);

protected:
  virtual void
  setDefaultIdentityInternal(const Name& identityName);

  virtual void
  setDefaultKeyNameForIdentityInternal(const Name& keyName);

  virtual void
  setDefaultCertificateNameForKeyInternal(const Name& certificateName);

  virtual void
  deleteCertificateInfo(const Name& certificateName);

  virtual void
  deletePublicKeyInfo(const Name& keyName);

  virtual void
  deleteIdentityInfo(const Name& identity);


private:
  class KeyRecord {
  public:
    KeyRecord(KeyType keyType, const PublicKey& key)
    : keyType_(keyType), key_(key)
    {
    }

    const KeyType getKeyType() const { return keyType_; }

    const PublicKey& getKey() { return key_; }

  private:
    KeyType   keyType_;
    PublicKey key_;
  };

  std::vector<std::string> identityStore_; /**< A list of name URI. */
  std::string defaultIdentity_;            /**< The default identity in identityStore_, or "" if not defined. */
  Name defaultKeyName_;
  Name defaultCert_;

  typedef std::map< std::string, ptr_lib::shared_ptr<KeyRecord> > KeyStore; /**< The map key is the keyName.toUri() */
  typedef std::map< std::string, ptr_lib::shared_ptr<IdentityCertificate> > CertificateStore; /**< The map key is the certificateName.toUri() */

  KeyStore keyStore_;
  CertificateStore certificateStore_;
};

} // namespace ndn

#endif //NDN_SECURITY_SEC_PUBLIC_INFO_MEMORY_HPP
