using System;
namespace MainNameSpace.Model.Data.Properties
{
    public abstract class PersistentProperty<TPropertyType> : ObservableProperty<TPropertyType>
    {
        protected TPropertyType _stored;
        private TPropertyType _defaultValue;


        public PersistentProperty(TPropertyType defaultValue)
        {
            _defaultValue = defaultValue;
        }

        public override TPropertyType Value
        {
            get => _stored;
            set
            {
                var IsEquals = _stored.Equals(value);
                if (IsEquals) return;
                var oldValue = _value;
                Write(_value);
                _stored = _value = value;
                InvokeChangedEvent(value, oldValue);
            }
        }
        protected void Init()
        {
            _stored = _value = Read(_defaultValue);
        }

        protected abstract void Write(TPropertyType value);
        protected abstract TPropertyType Read(TPropertyType defaultValue);

        public void Validate()
        {
            if (!_stored.Equals(_value))
            {
                Value = _value;
            }
        }
    }
}