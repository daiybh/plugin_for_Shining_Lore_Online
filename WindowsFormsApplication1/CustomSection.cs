
using System;
using System.Configuration;

namespace Guagua
{
    public class CustomSection : ConfigurationSection
    {
        private static ConfigurationPropertyCollection _Properties;
        // Internal flag to disable 
        // property setting.
        private static bool _ReadOnly;

        private static readonly ConfigurationProperty _EnableWork =
            new ConfigurationProperty("enableWork",
                typeof(bool), true,
                ConfigurationPropertyOptions.IsRequired);
        private static readonly ConfigurationProperty _Attack =
            new ConfigurationProperty("attack",
                typeof(bool), true,
                ConfigurationPropertyOptions.IsRequired);

        private static readonly ConfigurationProperty _PickUP =
            new ConfigurationProperty("pickUP",
                typeof(bool), true,
                ConfigurationPropertyOptions.IsRequired);

        private static readonly ConfigurationProperty _userName =
            new ConfigurationProperty("userName",
                typeof(string), "null",
                ConfigurationPropertyOptions.IsRequired);
        private static readonly ConfigurationProperty _fixedAttack =
           new ConfigurationProperty("fixedAttack",
              typeof(bool), false,
               ConfigurationPropertyOptions.IsRequired);


        public CustomSection()
        {
            _Properties =
                new ConfigurationPropertyCollection();

            _Properties.Add(_EnableWork);
            _Properties.Add(_Attack);
            _Properties.Add(_PickUP);
            _Properties.Add(_userName);
            _Properties.Add(_fixedAttack);
        }
        // This is a key customization. 
        // It returns the initialized property bag.
        protected override ConfigurationPropertyCollection Properties
        {
            get
            {
                return _Properties;
            }
        }


        private new bool IsReadOnly
        {
            get
            {
                return _ReadOnly;
            }
        }

        // Use this to disable property setting.
        private void ThrowIfReadOnly(string propertyName)
        {
            if (IsReadOnly)
                throw new ConfigurationErrorsException(
                    "The property " + propertyName + " is read only.");
        }

        public string userName
        {
            get { return (string)this["userName"]; }
            set
            {
                this["userName"] = value;
            }
        }
        public bool enableWork
        {
            get { return (bool)this["enableWork"]; }
            set
            {
                this["enableWork"] = value;
            }
        }
        public bool bAttack
        {
            get { return (bool)this["attack"]; }
            set
            {
                this["attack"] = value;
            }
        }
        public bool bFixedAttack
        {
            get { return (bool)this["fixedAttack"]; }
            set
            {
                this["fixedAttack"] = value;
            }
        }
        public bool bPickUP
        {
            get { return (bool)this["pickUP"]; }
            set
            {
                this["pickUP"] = value;
            }
        }
    }
}